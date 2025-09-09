#!/bin/sh
# Hatalarda çık, tanımsız değişken kullanımını ve pipe hatalarını yakala (DEBUG modunda izleme açılabilir)
set -eu
[ "${DEBUG:-0}" = "1" ] && set -x

# WordPress kök dizini ve wp-cli çağrısını hafıza limiti ile sarmalayan yardımcı fonksiyon
WP_PATH=/var/www/html
WP() { php -d memory_limit=512M /usr/local/bin/wp "$@"; }

# Veritabanı ve site temel değişkenleri (varsayılanlar)
: "${MYSQL_HOST:=mariadb}"
: "${MYSQL_DATABASE:=}"
: "${MYSQL_USER:=}"
: "${DOMAIN_NAME:=}"
: "${TITLE:=Inception WP}"

# Site URL’i: .env’de DOMAIN_NAME varsa https://DOMAIN_NAME kabul edilir, yoksa WP_URL veya localhost
SITE_URL="${WP_URL:-}"
[ -z "$SITE_URL" ] && [ -n "$DOMAIN_NAME" ] && SITE_URL="https://${DOMAIN_NAME}"

# DB parolası secrets'tan okunur; yoksa çık
DB_PASSWORD="$(cat /run/secrets/db_password 2>/dev/null || true)"
[ -n "$DB_PASSWORD" ] || { echo "[wp] HATA: /run/secrets/db_password boş ya da yok."; exit 1; }

# credentials dosyasındaki KEY=VAL satırlarını ortam değişkeni olarak içe aktar
if [ -f /run/secrets/credentials ]; then
  set -a
  . /run/secrets/credentials
  set +a
fi

# Geriye dönük adlar için eşitleme (eski değişkenleri de destekle)
: "${MYSQL_DATABASE:=${MYSQL_DB:-$MYSQL_DATABASE}}"
: "${MYSQL_USER:=${MYSQL_USERNAME:-$MYSQL_USER}}"
: "${MYSQL_HOST:=${WP_HOST:-$MYSQL_HOST}}"

# Yönetici hesap bilgileri (zorunlu)
: "${WP_ADMIN_NAME:=${ADMIN_USER:-${ADMIN_NAME:-}}}"
: "${WP_ADMIN_PASSWORD:=${ADMIN_PASSWORD:-}}"
: "${WP_ADMIN_EMAIL:=${ADMIN_EMAIL:-}}"
[ -n "$WP_ADMIN_NAME" ] && [ -n "$WP_ADMIN_PASSWORD" ] && [ -n "$WP_ADMIN_EMAIL" ] || { echo "[wp] HATA: admin bilgileri eksik."; exit 1; }

# Opsiyonel ikinci kullanıcı
: "${WP_USER_NAME:=${WP_USER_LOGIN:-}}"
WP_USER_PASS="${WP_USER_PASSWORD:-}"
WP_USER_MAIL="${WP_USER_EMAIL:-}"

# Zorunlu veritabanı bilgileri kontrolü
[ -n "$MYSQL_DATABASE" ] && [ -n "$MYSQL_USER" ] || { echo "[wp] HATA: MYSQL_DATABASE/MYSQL_USER eksik."; exit 1; }

# Dizin hazırlığı ve sahiplik ayarı
mkdir -p "$WP_PATH"
chown -R www-data:www-data "$WP_PATH"

# WordPress çekirdeğini indir (yoksa)
if [ ! -f "$WP_PATH/wp-includes/version.php" ]; then
  WP core download --path="$WP_PATH" --allow-root
fi

# wp-config oluştur (yoksa): DB bilgileri, tuzlar ve dosya sistemi yöntemi
if [ ! -f "$WP_PATH/wp-config.php" ]; then
  WP config create --path="$WP_PATH" --allow-root \
    --dbname="$MYSQL_DATABASE" --dbuser="$MYSQL_USER" --dbpass="$DB_PASSWORD" --dbhost="$MYSQL_HOST" --dbprefix="wp_" --skip-check
  WP config shuffle-salts --path="$WP_PATH" --allow-root
  WP config set FS_METHOD direct --path="$WP_PATH" --allow-root
fi

# İlk kurulum: site başlığı/URL ve admin bilgileri ile kur
if ! WP core is-installed --path="$WP_PATH" --allow-root >/dev/null 2>&1; then
  [ -n "$SITE_URL" ] || SITE_URL="http://localhost"
  WP core install --path="$WP_PATH" --allow-root \
    --url="$SITE_URL" --title="$TITLE" \
    --admin_user="$WP_ADMIN_NAME" --admin_password="$WP_ADMIN_PASSWORD" --admin_email="$WP_ADMIN_EMAIL"
  # Opsiyonel kullanıcıyı oluştur
  if [ -n "$WP_USER_NAME" ] && [ -n "$WP_USER_PASS" ] && [ -n "$WP_USER_MAIL" ]; then
    WP user create --path="$WP_PATH" --allow-root "$WP_USER_NAME" "$WP_USER_MAIL" --user_pass="$WP_USER_PASS" --role=author
  fi
fi

# Güvenli izinler: dizinler 755, dosyalar 644
find "$WP_PATH" -type d -exec chmod 755 {} \;
find "$WP_PATH" -type f -exec chmod 644 {} \;

# Docker CMD'sini çalıştır (php-fpm)
exec "$@"
