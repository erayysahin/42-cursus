FROM alpine:3.21

ARG PHPV=83
ENV TZ=Europe/Istanbul

RUN apk add --no-cache \
    curl ca-certificates tar less tzdata \
    netcat-openbsd \
    php${PHPV} php${PHPV}-fpm php${PHPV}-cli php${PHPV}-common \
    php${PHPV}-mysqli php${PHPV}-mbstring php${PHPV}-curl \
    php${PHPV}-xml php${PHPV}-zip php${PHPV}-gd php${PHPV}-intl \
    php${PHPV}-phar php${PHPV}-opcache \
    php${PHPV}-tokenizer


# WP-CLI 'php'ı /usr/bin/php ile çağırır; garanti için symlink
RUN ln -sf /usr/bin/php${PHPV} /usr/bin/php

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
    > /etc/php${PHPV}/conf.d/99-opcache.ini

RUN echo "memory_limit=512M" > /etc/php${PHPV}/conf.d/zz-cli-memory.ini

# PHP-FPM havuzu
COPY conf/www.conf /etc/php${PHPV}/php-fpm.d/www.conf

# Entrypoint
COPY ./tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

EXPOSE 9000

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["sh","-lc","exec php-fpm83 -F"]
