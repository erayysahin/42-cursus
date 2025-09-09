# Temel imaj: Küçük ve güvenli bir taban için Alpine Linux
FROM alpine:3.21

# Paketler ve hazırlık:
# - mariadb: MariaDB sunucusu
# - mariadb-client: yönetim/komut satırı araçları (mysql, mariadb)
# - tzdata: saat dilimi verileri (loglar ve zaman ayarları için)
# Dizinler:
# - /run/mysqld: PID ve socket dosyaları için
# Sahiplik:
# - /run/mysqld ve /var/lib/mysql mysql kullanıcısına atanır
RUN apk add --no-cache mariadb mariadb-client tzdata \
    && mkdir -p /run/mysqld \
    && chown -R mysql:mysql /run/mysqld /var/lib/mysql

# Giriş (entrypoint) betiği: ilk başlatma, kullanıcı/DB oluşturma ve sunucuyu çalıştırma
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
# Çalıştırma izni ver
RUN chmod +x /usr/local/bin/entrypoint.sh

# MariaDB varsayılan portu (3306) dışa açılır (belgeleme amaçlı)
EXPOSE 3306

# Konteyner başlangıcında çalışacak betik
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
# MariaDB sunucusunu ön planda çalıştır
CMD ["mariadbd", "--user=mysql", "--datadir=/var/lib/mysql", "--pid-file=/run/mysqld/mysqld.pid"]
