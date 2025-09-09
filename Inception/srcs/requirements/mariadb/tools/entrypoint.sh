#!/bin/sh
# Katı mod: hata, tanımsız değişken ve pipe hatalarında çık
set -euo pipefail

# Windows satır sonlarını ve sondaki boşlukları temizlemek için yardımcı fonksiyon
trim() { tr -d '\r' | sed 's/[[:space:]]*$//'; }

# Root ve uygulama kullanıcısı şifrelerini Docker secrets'tan oku
ROOT_PASS="$(cat /run/secrets/db_root_password | trim)"
USER_PASS="$(cat /run/secrets/db_password      | trim)"

# credentials dosyasından veritabanı adı ve kullanıcıyı çek
DB_NAME=""
DB_USER=""
if [ -f /run/secrets/credentials ]; then
  DB_NAME="$(grep -E '^MYSQL_DATABASE=' /run/secrets/credentials | cut -d= -f2- | trim || true)"
  DB_USER="$(grep -E '^MYSQL_USER='     /run/secrets/credentials | cut -d= -f2- | trim || true)"
fi

# Zorunlu alan kontrolü: DB adı ve kullanıcı yoksa çık
[ -z "${DB_NAME}" ] && { echo "[mariadb] MYSQL_DATABASE yok (credentials)."; exit 1; }
[ -z "${DB_USER}" ] && { echo "[mariadb] MYSQL_USER yok (credentials)."; exit 1; }

# Uzak bağlantılar için varsayılan konfig ayarlarını güncelle
sed -i "s|skip-networking|# skip-networking|g" /etc/my.cnf.d/mariadb-server.cnf || true
sed -i "s|.*bind-address\s*=.*|bind-address=0.0.0.0|g" /etc/my.cnf.d/mariadb-server.cnf || true

# İlk kurulum: sistem tabloları yoksa veritabanını başlat
if [ ! -d /var/lib/mysql/mysql ]; then
  # Alpine'de mariadb-install-db veya mysql_install_db olabilir; hangisi varsa onu kullan
  if command -v mariadb-install-db >/dev/null 2>&1; then
    mariadb-install-db --basedir=/usr --datadir=/var/lib/mysql --user=mysql
  else
    mysql_install_db --basedir=/usr --datadir=/var/lib/mysql --user=mysql --rpm
  fi

  # Socket/PID için çalışma dizini
  mkdir -p /run/mysqld
  chown -R mysql:mysql /run/mysqld

  # Geçici sunucuyu local socket ile başlat (root parolası henüz yok)
  SERVER_BIN="/usr/bin/mariadbd"; [ -x "$SERVER_BIN" ] || SERVER_BIN="/usr/bin/mysqld"
  $SERVER_BIN \
    --user=mysql \
    --datadir=/var/lib/mysql \
    --socket=/run/mysqld/mysqld.sock \
    --pid-file=/run/mysqld/mysqld.pid \
    --bind-address=127.0.0.1 \
    --skip-networking=0 &
  pid="$!"

  # Sunucu hazır olana kadar bekle
  for i in $(seq 1 60); do
    [ -S /run/mysqld/mysqld.sock ] && mariadb --protocol=SOCKET -uroot -S /run/mysqld/mysqld.sock -e "SELECT 1" && break
    sleep 1
  done

  # Root parolasını ayarla, veritabanını ve kullanıcıyı oluştur, yetkileri ver
  mariadb --protocol=SOCKET -uroot -S /run/mysqld/mysqld.sock <<SQL
ALTER USER 'root'@'localhost' IDENTIFIED BY '${ROOT_PASS}';
CREATE DATABASE IF NOT EXISTS \`${DB_NAME}\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER IF NOT EXISTS '${DB_USER}'@'%' IDENTIFIED BY '${USER_PASS}';
GRANT ALL PRIVILEGES ON \`${DB_NAME}\`.* TO '${DB_USER}'@'%';
FLUSH PRIVILEGES;
SQL

  # Geçici sunucuyu güvenli şekilde kapat
  mariadb-admin --protocol=SOCKET -uroot -p"${ROOT_PASS}" -S /run/mysqld/mysqld.sock shutdown || true
  wait "$pid" || true
fi

# Son: girilen komutu (CMD) çalıştır
echo "[mariadb] starting mysqld..."
exec "$@"
