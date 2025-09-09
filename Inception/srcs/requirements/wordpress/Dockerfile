# Taban imaj: minimal Alpine Linux (küçük ve hızlı)
FROM alpine:3.21

# Gerekli paketler:
# - curl, ca-certificates: dosya indirme ve TLS doğrulama
# - tar, tzdata, netcat-openbsd: arşiv, saat dilimi ve healthcheck için nc
# - php83, php83-fpm, php83-cli, php83-common: PHP 8.3 ve FPM
# - php83-mysqli, -mbstring, -curl, -xml, -zip, -gd, -intl, -phar, -opcache, -tokenizer: WordPress ve eklentileri için yaygın uzantılar
RUN apk add --no-cache \
    curl ca-certificates tar tzdata netcat-openbsd \
    php83 php83-fpm php83-cli php83-common \
    php83-mysqli php83-mbstring php83-curl \
    php83-xml php83-zip php83-gd php83-intl \
    php83-phar php83-opcache php83-tokenizer

# php komutunu php83 ikilisine yönlendir (wp-cli gibi araçlar php bekler)
RUN ln -sf /usr/bin/php83 /usr/bin/php

# www-data kullanıcısını/grubunu oluştur, web kökünü hazırla ve izinleri ayarla
RUN addgroup -S www-data 2>/dev/null || true \
    && adduser -S -D -H -G www-data www-data 2>/dev/null || true \
    && mkdir -p /var/www/html \
    && chown -R www-data:www-data /var/www/html

# Çalışma dizini: WordPress kökü
WORKDIR /var/www/html

# WP-CLI indir ve çalıştırılabilir yap (WordPress kurulum/otomasyon için)
RUN curl -fsSL -o /usr/local/bin/wp https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x /usr/local/bin/wp

# CLI için PHP bellek sınırını artır (büyük kurulumlarda hataları önler)
RUN echo "memory_limit=512M" > /etc/php83/conf.d/zz-cli-memory.ini

# PHP-FPM havuz konfigürasyonu ve entrypoint betiğini imaja kopyala
COPY conf/www.conf /etc/php83/php-fpm.d/www.conf
COPY ./tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

# PHP-FPM FastCGI portu
EXPOSE 9000
# Entrypoint: WordPress kurulum akışı ve sonunda php-fpm başlatma
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["sh","-lc","exec php-fpm83 -F"]
