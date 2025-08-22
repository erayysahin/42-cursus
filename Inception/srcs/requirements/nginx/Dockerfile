FROM alpine:3.21

RUN apk add --no-cache nginx openssl

# Konfig dosyası
COPY conf/nginx.conf /etc/nginx/nginx.conf

# Entrypoint: sertifika üret + placeholder doldur + nginx başlat
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh \
 && mkdir -p /var/www/html /etc/nginx/ssl

EXPOSE 443
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
