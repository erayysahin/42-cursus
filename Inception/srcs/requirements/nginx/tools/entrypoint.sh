#!/bin/sh
set -euo pipefail

: "${DOMAIN_NAME:?DOMAIN_NAME yok (.env içinde olmalı)}"
: "${CRT:=/etc/nginx/ssl/nginx.crt}"
: "${KEY:=/etc/nginx/ssl/nginx.key}"
: "${SUBJECT:=/CN=${DOMAIN_NAME}}"

mkdir -p "$(dirname "$CRT")" "$(dirname "$KEY")"

# Sertifika yoksa üret
if [ ! -f "$CRT" ] || [ ! -f "$KEY" ]; then
  openssl req -x509 -nodes -days 365 -newkey rsa:4096 \
    -keyout "$KEY" -out "$CRT" -subj "$SUBJECT"
fi

# Placeholder'ları doldur
sed -i \
  -e "s|!SERVER_NAME!|$DOMAIN_NAME|g" \
  -e "s|!CRT!|$CRT|g" \
  -e "s|!KEY!|$KEY|g" \
  /etc/nginx/http.d/default.conf


exec nginx -g 'daemon off;'
