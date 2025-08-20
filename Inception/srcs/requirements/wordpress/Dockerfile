FROM alpine:3.21

ARG PHPV=83
ENV TZ=Europe/Istanbul

RUN apk add --no-cache \
    curl ca-certificates tar less tzdata \
    netcat-openbsd \
    php${PHPV} php${PHPV}-fpm php${PHPV}-cli php${PHPV}-common \
    php${PHPV}-mysqli php${PHPV}-mbstring php${PHPV}-curl \
    php${PHPV}-xml php${PHPV}-zip php${PHPV}-gd php${PHPV}-intl \
    php${PHPV}-phar php${PHPV}-opcache

RUN addgroup -g 82 -S www-data \
 && adduser -S -D -H -u 82 -G www-data www-data \
 && mkdir -p /var/www/html \
 && chown -R www-data:www-data /var/www/html

WORKDIR /var/www/html

RUN curl -fsSL -o /usr/local/bin/wp https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
 && chmod +x /usr/local/bin/wp

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime \
 && echo $TZ > /etc/timezone

RUN printf "opcache.enable=1\nopcache.memory_consumption=128\nopcache.validate_timestamps=0\n" \
    > /etc/php${PHPV}/conf.d/99-opcache.ini

COPY conf/www.conf /etc/php${PHPV}/php-fpm.d/www.conf

COPY ./tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

EXPOSE 9000

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["sh","-lc","exec php-fpm${PHPV} -F"]
