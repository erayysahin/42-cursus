FROM alpine:3.21

RUN apk add --no-cache nginx openssl

# COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY conf/nginx.conf /etc/nginx/http.d/default.conf

COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh \
    && mkdir -p /var/www/html /etc/nginx/ssl

EXPOSE 443
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]