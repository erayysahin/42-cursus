#!/bin/sh
# Hatalarda çık, tanımsız değişken ve pipe hatalarını yakala
set -euo pipefail

# Gerekli ortam değişkenleri ve varsayılan yollar
: "${DOMAIN_NAME:?DOMAIN_NAME yok (.env içinde olmalı)}"
: "${CRT:=/etc/nginx/ssl/nginx.crt}"
: "${KEY:=/etc/nginx/ssl/nginx.key}"
: "${SUBJECT:=/CN=${DOMAIN_NAME}}"

# Sertifika ve anahtar için klasörleri oluştur
mkdir -p "$(dirname "$CRT")" "$(dirname "$KEY")"

# Sertifika yoksa self-signed bir sertifika üret
if [ ! -f "$CRT" ] || [ ! -f "$KEY" ]; then
  openssl req -x509 -nodes -days 365 -newkey rsa:4096 \
    -keyout "$KEY" -out "$CRT" -subj "$SUBJECT"
fi

# NGINX konfigürasyonundaki yer tutucuları (.env ve secrets ile) gerçek değerlere çevir
sed -i \
  -e "s|¿SVNAME?|$DOMAIN_NAME|g" \
  -e "s|¿CERTFC?|$CRT|g" \
  -e "s|¿KEY?|$KEY|g" \
  /etc/nginx/http.d/default.conf

# NGINX'i ön planda çalıştır
exec nginx -g 'daemon off;'
