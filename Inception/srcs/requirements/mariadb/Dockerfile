FROM alpine:3.21

RUN apk add --no-cache mariadb mariadb-client tzdata


# Entrypoint
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh \
    && mkdir -p /run/mysqld \
    && chown -R mysql:mysql /run/mysqld /var/lib/mysql

VOLUME ["/var/lib/mysql"]
EXPOSE 3306

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["mariadbd", "--user=mysql", "--datadir=/var/lib/mysql", "--pid-file=/run/mysqld/mysqld.pid"]
