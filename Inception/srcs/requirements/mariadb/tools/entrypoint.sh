#!/bin/sh
set -euo pipefail

trim() { tr -d '\r' | sed 's/[[:space:]]*$//'; }

ROOT_PASS="$(cat /run/secrets/db_root_password | trim)"
USER_PASS="$(cat /run/secrets/db_password      | trim)"

DB_NAME=""
DB_USER=""
if [ -f /run/secrets/credentials ]; then
  DB_NAME="$(grep -E '^MYSQL_DATABASE=' /run/secrets/credentials | cut -d= -f2- | trim || true)"
  DB_USER="$(grep -E '^MYSQL_USER='     /run/secrets/credentials | cut -d= -f2- | trim || true)"
fi

[ -z "${DB_NAME}" ] && { echo "[mariadb] MYSQL_DATABASE yok (credentials)."; exit 1; }
[ -z "${DB_USER}" ] && { echo "[mariadb] MYSQL_USER yok (credentials)."; exit 1; }
sed -i "s|skip-networking|# skip-networking|g" /etc/my.cnf.d/mariadb-server.cnf || true
sed -i "s|.*bind-address\s*=.*|bind-address=0.0.0.0|g" /etc/my.cnf.d/mariadb-server.cnf || true

if [ ! -d /var/lib/mysql/mysql ]; then
  echo "[mariadb] initializing system tables..."
  if command -v mariadb-install-db >/dev/null 2>&1; then
    mariadb-install-db --basedir=/usr --datadir=/var/lib/mysql --user=mysql
  else
    mysql_install_db --basedir=/usr --datadir=/var/lib/mysql --user=mysql --rpm
  fi

  # my.cnf ayarları (remote için)
  sed -i "s|skip-networking|# skip-networking|g" /etc/my.cnf.d/mariadb-server.cnf || true
  sed -i "s|.*bind-address\s*=.*|bind-address=0.0.0.0|g" /etc/my.cnf.d/mariadb-server.cnf || true

 echo "[mariadb] starting temporary server..."

# SOCKET DİZİNİ
mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld

# mariadbd varsa onu, yoksa mysqld’yi kullan
SERVER_BIN="/usr/bin/mariadbd"
[ -x "$SERVER_BIN" ] || SERVER_BIN="/usr/bin/mysqld"

# HATALI BAYRAK YOK! (log-error-verbosity’yi kaldırdık)
$SERVER_BIN \
  --user=mysql \
  --datadir=/var/lib/mysql \
  --socket=/run/mysqld/mysqld.sock \
  --pid-file=/run/mysqld/mysqld.pid \
  --bind-address=127.0.0.1 \
  --skip-networking=0 &

pid="$!"

# hazır olana kadar bekle (socket var mı?)
for i in $(seq 1 60); do
  [ -S /run/mysqld/mysqld.sock ] && mariadb --protocol=SOCKET -uroot -S /run/mysqld/mysqld.sock -e "SELECT 1" && break
  sleep 1
done

echo "[mariadb] provisioning users & db..."
mariadb --protocol=SOCKET -uroot -S /run/mysqld/mysqld.sock <<SQL
ALTER USER 'root'@'localhost' IDENTIFIED BY '${ROOT_PASS}';
CREATE DATABASE IF NOT EXISTS \`${DB_NAME}\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER IF NOT EXISTS '${DB_USER}'@'%' IDENTIFIED BY '${USER_PASS}';
GRANT ALL PRIVILEGES ON \`${DB_NAME}\`.* TO '${DB_USER}'@'%';
FLUSH PRIVILEGES;
SQL

echo "[mariadb] shutting down temporary server..."
# Aynı socket üzerinden kapat (artık parola var)
mariadb-admin --protocol=SOCKET -uroot -p"${ROOT_PASS}" -S /run/mysqld/mysqld.sock shutdown || true
wait "$pid" || true
fi

# (init edilmiş olsun ya da olmasın) son ayarlar

echo "[mariadb] starting mysqld..."
exec "$@"
