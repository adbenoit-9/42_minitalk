# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/25 23:32:24 by adbenoit          #+#    #+#              #
#    Updated: 2021/10/13 15:34:31 by adbenoit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER 		=	server
CLIENT 		=	client

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

LIB_DIR		=	libft
LIB			=	$(LIB_DIR)/libft.a


all: $(LIB) $(SERVER) $(CLIENT)

$(LIB) :
	@make -C $(LIB_DIR)

$(SERVER): $(SERVER).o
	@$(CC) $(CFLAGS) $(SERVER).o -o $(SERVER) $(LIB) && ([ $$? -eq 0 ] \
	&& echo "Compilation of \033[33;1m$(SERVER)\033[0;1m: [\033[1;32mOK\033[0;1m]\033[0m") \
	|| echo "Compilation of \033[33;1m$(SERVER)\033[0;1m: [\033[1;31mKO\033[0;1m]\033[0m"
	
$(CLIENT): $(CLIENT).o
	@$(CC) $(CFLAGS) $(CLIENT).o -o $(CLIENT) $(LIB) && ([ $$? -eq 0 ] \
	&& echo "Compilation of \033[33;1m$(CLIENT)\033[0;1m: [\033[1;32mOK\033[0;1m]\033[0m") \
	|| echo "Compilation of \033[33;1m$(CLIENT)\033[0;1m: [\033[1;31mKO\033[0;1m]\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIB_DIR) clean
	@rm -rf $(SERVER).o $(CLIENT).o
	@echo "\033[33;1mMinitalk\033[0;1m: objects deleted\033[0m"

fclean:
	@make -C $(LIB_DIR) fclean
	@rm -rf $(SERVER) $(CLIENT) $(SERVER).o $(CLIENT).o
	@echo "\033[33;1mMinitalk\033[0;1m: objects deleted\033[0m"
	@echo "\033[33;1m$(SERVER)\033[0;1m: $(SERVER) deleted\033[0m"
	@echo "\033[33;1m$(CLIENT)\033[0;1m: $(CLIENT) deleted\033[0m"

re: fclean all

debug:
	@echo "\033[34;1mCLIENT\033[0;m = $(CLIENT)"
	@echo "\033[34;1mSERVERER\033[0;m = $(SERVER)"

.PHONY: all clean fclean re debug
