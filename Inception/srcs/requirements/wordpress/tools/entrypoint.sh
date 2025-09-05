#!/bin/sh
set -eu
[ "${DEBUG:-0}" = "1" ] && set -x

WP_PATH=/var/www/html

# ---- WP-CLI bellek düzeltmesi ----
# PHAR açarken bellek taşmasını önlemek için tüm wp komutlarını bu wrapper ile çağır.
WP() { php -d memory_limit=512M /usr/local/bin/wp "$@"; }

: "${MYSQL_HOST:=mariadb}"
: "${MYSQL_DATABASE:=}"
: "${MYSQL_USER:=}"
: "${DOMAIN_NAME:=}"
: "${TITLE:=Inception WP}"

SITE_URL="${WP_URL:-}"
[ -z "$SITE_URL" ] && [ -n "$DOMAIN_NAME" ] && SITE_URL="https://${DOMAIN_NAME}"

# Secrets
DB_PASSWORD="$(cat /run/secrets/db_password 2>/dev/null || true)"
[ -n "$DB_PASSWORD" ] || { echo "[wp] HATA: /run/secrets/db_password boş ya da yok."; exit 1; }

# credentials dosyasını yükle (KEY=VAL satırları)
if [ -f /run/secrets/credentials ]; then
  set -a
  . /run/secrets/credentials
  set +a
fi

# Eski isimlerle gelen değerleri de destekle
: "${MYSQL_DATABASE:=${MYSQL_DB:-$MYSQL_DATABASE}}"
: "${MYSQL_USER:=${MYSQL_USERNAME:-$MYSQL_USER}}"
: "${MYSQL_HOST:=${WP_HOST:-$MYSQL_HOST}}"


: "${WP_ADMIN_NAME:=${ADMIN_USER:-${ADMIN_NAME:-}}}"
: "${WP_ADMIN_PASSWORD:=${ADMIN_PASSWORD:-}}"
: "${WP_ADMIN_EMAIL:=${ADMIN_EMAIL:-}}"
[ -n "$WP_ADMIN_NAME" ]     || { echo "[wp] HATA: WP_ADMIN_NAME/ADMIN_* yok."; exit 1; }
[ -n "$WP_ADMIN_PASSWORD" ] || { echo "[wp] HATA: WP_ADMIN_PASSWORD/ADMIN_PASSWORD yok."; exit 1; }
[ -n "$WP_ADMIN_EMAIL" ]    || { echo "[wp] HATA: WP_ADMIN_EMAIL/ADMIN_EMAIL yok."; exit 1; }

# İkinci kullanıcı (opsiyonel)
: "${WP_USER_NAME:=${WP_USER_LOGIN:-}}"
WP_USER_PASS="${WP_USER_PASSWORD:-}"
WP_USER_MAIL="${WP_USER_EMAIL:-}"

# Zorunlu alan kontrolü
[ -n "$MYSQL_DATABASE" ] || { echo "[wp] HATA: MYSQL_DATABASE eksik."; exit 1; }
[ -n "$MYSQL_USER" ]     || { echo "[wp] HATA: MYSQL_USER eksik."; exit 1; }

# Dizin ve sahiplik
mkdir -p "$WP_PATH"
chown -R www-data:www-data "$WP_PATH"

# WordPress çekirdeği
if [ ! -f "$WP_PATH/wp-includes/version.php" ]; then
  echo "[wp] core download"
  wp core download --path="$WP_PATH" --allow-root
fi


# wp-config
if [ ! -f "$WP_PATH/wp-config.php" ]; then
  echo "[wp] config create"
  wp config create --path="$WP_PATH" --allow-root \
    --dbname="$MYSQL_DATABASE" \
    --dbuser="$MYSQL_USER" \
    --dbpass="$DB_PASSWORD" \
    --dbhost="$MYSQL_HOST" \
    --dbprefix="wp_" \
    --skip-check

  wp config shuffle-salts        --path="$WP_PATH" --allow-root
  wp config set FS_METHOD direct --path="$WP_PATH" --allow-root
fi

# İlk kurulum
if ! wp core is-installed --path="$WP_PATH" --allow-root >/dev/null 2>&1; then
  if [ -z "$SITE_URL" ]; then
    echo "[wp] Uyarı: SITE_URL yok, http://localhost kullanılacak."
    SITE_URL="http://localhost"
  fi

  echo "[wp] core install (${SITE_URL})"
  wp core install --path="$WP_PATH" --allow-root \
    --url="$SITE_URL" \
    --title="$TITLE" \
    --admin_user="$WP_ADMIN_NAME" \
    --admin_password="$WP_ADMIN_PASSWORD" \
    --admin_email="$WP_ADMIN_EMAIL"

  if [ -n "$WP_USER_NAME" ] && [ -n "$WP_USER_PASS" ] && [ -n "$WP_USER_MAIL" ]; then
    wp user create --path="$WP_PATH" --allow-root \
      "$WP_USER_NAME" "$WP_USER_MAIL" --user_pass="$WP_USER_PASS" --role=author
  fi
fi

# İzinler
find "$WP_PATH" -type d -exec chmod 755 {} \;
find "$WP_PATH" -type f -exec chmod 644 {} \;

echo "[wp] starting php-fpm…"
exec "$@"
