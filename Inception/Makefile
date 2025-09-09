COMPOSE=docker compose
DIR=srcs

.PHONY: up down build fclean re logs

up:
	sudo mkdir -p ~/data/wordpress
	sudo mkdir -p ~/data/mariadb
	@$(COMPOSE) -f $(DIR)/docker-compose.yml up -d

down:
	@$(COMPOSE) -f $(DIR)/docker-compose.yml down

build:
	@$(COMPOSE) -f $(DIR)/docker-compose.yml build --no-cache

fclean:
	sudo rm -rf ~/data/*
	@$(COMPOSE) -f $(DIR)/docker-compose.yml down -v --remove-orphans
	@docker system prune -af

re: fclean build up

logs:
	@$(COMPOSE) -f $(DIR)/docker-compose.yml logs -f
