FROM alpine:3.21

ARG PHPV=83
ENV TZ=Europe/Istanbul

RUN apk add --no-cache \
    curl ca-certificates tar less tzdata \
    netcat-openbsd \
    php83 php83-fpm php83-cli php83-common \
    php83-mysqli php83-mbstring php83-curl \
    php83-xml php83-zip php83-gd php83-intl \
    php83-phar php83-opcache \
    php83-tokenizer


# WP-CLI 'php'ı /usr/bin/php ile çağırır; garanti için symlink
RUN ln -sf /usr/bin/php83 /usr/bin/php

# www-data ve web kökü (varsa yeniden yaratmaya çalışma)
RUN if ! grep -qE '^www-data:' /etc/group; then addgroup -S www-data; fi \
    && if ! id -u www-data >/dev/null 2>&1; then adduser -S -D -H -G www-data www-data; fi \
    && mkdir -p /var/www/html \
    && chown -R www-data:www-data /var/www/html

WORKDIR /var/www/html

# WP-CLI (healthcheck ve kurulum için)
RUN curl -fsSL -o /usr/local/bin/wp https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x /usr/local/bin/wp

# Sistem zaman dilimi
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime \
    && echo $TZ > /etc/timezone

# (Opsiyonel) OPcache iyileştirmeleri
RUN printf "opcache.enable=1\nopcache.memory_consumption=128\nopcache.validate_timestamps=0\n" \
    > /etc/php83/conf.d/99-opcache.ini

RUN echo "memory_limit=512M" > /etc/php83/conf.d/zz-cli-memory.ini

# PHP-FPM havuzu
COPY conf/www.conf /etc/php83/php-fpm.d/www.conf

# Entrypoint
COPY ./tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

EXPOSE 9000

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["sh","-lc","exec php-fpm83 -F"]
