# Taban imaj: küçük, hızlı ve güvenli Alpine Linux
FROM alpine:3.21

# Paket kurulumu:
# - nginx: web sunucusu
# - openssl: self-signed SSL sertifikası üretimi ve kripto araçları
# Ayrıca gerekli dizinleri oluştur (web kökü ve SSL klasörü)
RUN apk add --no-cache nginx openssl \
    && mkdir -p /var/www/html /etc/nginx/ssl

# Site/Nginx yapılandırmasını imaja kopyala (default server)
COPY conf/nginx.conf /etc/nginx/http.d/default.conf
# Başlangıç betiğini kopyala (sertifika üretimi + placeholder doldurma + nginx başlatma)
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
# Betiği çalıştırılabilir yap
RUN chmod +x /usr/local/bin/entrypoint.sh

# HTTPS için 443 portunu dışa aç (belgeleme amaçlı)
EXPOSE 443
# Konteyner başlangıcında çalışacak komut
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]