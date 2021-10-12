# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/25 23:32:24 by adbenoit          #+#    #+#              #
#    Updated: 2021/10/12 20:33:46 by adbenoit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER 		=	server
CLIENT 		=	client

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

LIB_DIR		=	libft
LIB			=	$(LIB_DIR)/libft.a


all: $(LIB) $(SERVER) $(CLIENT)

$(LIB) :
	@make -C $(LIB_DIR)

$(SERVER):
	@$(CC) $(CFLAGS) $(SERVER).c -o $(SERVER) $(LIB) && ([ $$? -eq 0 ] \
	&& echo "Compilation of \033[33;1m$(SERVER)\033[0;1m: [\033[1;32mOK\033[0;1m]\033[0m") \
	|| echo "Compilation of \033[33;1m$(SERVER)\033[0;1m: [\033[1;31mKO\033[0;1m]\033[0m"
	
$(CLIENT):
	@$(CC) $(CFLAGS) $(CLIENT).c -o $(CLIENT) $(LIB) && ([ $$? -eq 0 ] \
	&& echo "Compilation of \033[33;1m$(CLIENT)\033[0;1m: [\033[1;32mOK\033[0;1m]\033[0m") \
	|| echo "Compilation of \033[33;1m$(CLIENT)\033[0;1m: [\033[1;31mKO\033[0;1m]\033[0m"

clean:
	@make -C $(LIB_DIR) clean

fclean:
	@rm -rf $(SERVER)
	@rm -rf $(CLIENT)
	@echo "\033[33;1m$(SERVER)\033[0;1m: $(SERVER) deleted\033[0m"
	@echo "\033[33;1m$(CLIENT)\033[0;1m: $(CLIENT) deleted\033[0m"
# make -C $(LIB_DIR) fclean

re: fclean all

debug:
	@echo "\033[34;1mCLIENT\033[0;m = $(CLIENT)"
	@echo "\033[34;1mSERVERER\033[0;m = $(SERVER)"

.PHONY: all clean fclean re debug
