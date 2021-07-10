# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/25 23:32:24 by adbenoit          #+#    #+#              #
#    Updated: 2021/07/10 14:21:12 by adbenoit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_PATH	=	
OBJ_PATH	=	obj/

SERV 		=	server

S_SRC		=	server.c

S_OBJ_NAME	=	$(S_SRC:.c=.o)

S_OBJ		=	$(addprefix $(OBJ_PATH),$(S_OBJ_NAME))


CLIENT 		=	client

C_SRC		=	client.c

C_OBJ_NAME	=	$(C_SRC:.c=.o)

C_OBJ		=	$(addprefix $(OBJ_PATH),$(C_OBJ_NAME))


CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

LIB_DIR		=	libft

LIB			=	$(LIB_DIR)/libft.a


all: $(S_SRC_OBJ) $(C_SRC_OBJ) $(LIB)
	@$(CC) $(CFLAGS) $(S_SRC) -o server $(LIB)
	@echo "Compilation of \033[33;1m$(SERV)\033[0;1m: [\033[1;32mOK\033[0;1m]\033[0m"
	@$(CC) $(CFLAGS) $(C_SRC) -o client $(LIB)
	@echo "Compilation of \033[33;1m$(CLIENT)\033[0;1m: [\033[1;32mOK\033[0;1m]\033[0m"

$(LIB) :
	@make -C $(LIB_DIR)

clean:
	@rm -f $(S_OBJ)
	@rm -f $(C_OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "\033[33;1m$(SERV)\033[0;1m: objects deleted\033[0m"
	@echo "\033[33;1m$(CLIENT)\033[0;1m: objects deleted\033[0m"

fclean:	clean
	@rm -rf $(SERV)
	@rm -rf $(CLIENT)
	@echo "\033[33;1m$(SERV)\033[0;1m: $(SERV) deleted\033[0m"
	@echo "\033[33;1m$(CLIENT)\033[0;1m: $(CLIENT) deleted\033[0m"
	@make -C $(LIB_DIR) fclean

re: fclean all

FILE=norme_error.txt
ERROR= `cat $(FILE) | grep -B 1 "Error"`
norme:
	@make -C $(LIB_DIR) norme
	@printf "\033[33mLaunching ...\033[0m"
	@norminette */*/*c */*c */*h > $(FILE)
	@printf "\rNorme of \033[33;1m$(NAME)\033[0;1m: [\033[1;32mOK\033[0;1m]\033[0m"
	@ echo "\r$(ERROR)"
	@rm $(FILE)

debug:
	@echo "\033[34;1mCLIENT SRC\033[0;m = $(C_SRC)"
	@echo "\033[34;1mSERVER SRC\033[0;m = $(S_SRC)\n"
	@echo "\033[34;1mCLIENT OBJ\033[0;m = $(C_OBJ)"
	@echo "\033[34;1mSERVER OBJ\033[0;m = $(S_OBJ)"

.PHONY: all clean fclean re run
