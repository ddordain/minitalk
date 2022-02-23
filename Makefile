# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 13:55:42 by ddordain          #+#    #+#              #
#    Updated: 2022/02/23 12:55:34 by ddordain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean re fclean

NAME 		=	server
NAME2		=	client
LIBFT 		= 	libft.a
LIB_DIR		=	libft/
OBJ_DIR		=	obj/
OBJ_DIR2	=	obj2/
SRCS_DIR	=	src/
SRCS		=	server.c
SRCS2		=	client.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
OBJS2 = $(addprefix $(OBJ_DIR2), $(SRCS2:.c=.o))

LFLAGS = -I include/
CFLAGS = -Wall -Wextra -Werror
DEBUGGING = -ggdb
CC = gcc
RM = rm -rf
AR = ar rc

RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PINK = \033[35m
CYAN = \033[36m



all: $(NAME) $(NAME2)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c ./include/minitalk.h
		@echo Create: $(NAME) Object directory
		@mkdir -p $(OBJ_DIR)
		$(CC) -c $(CFLAGS) $(DEBUGGING) $(LFLAGS) $< -o $@
$(OBJ_DIR2)%.o : $(SRCS_DIR)%.c ./include/minitalk.h
		@echo Create: $(NAME2) Object directory
		@mkdir -p $(OBJ_DIR2)
		$(CC) -c $(CFLAGS) $(DEBUGGING) $(LFLAGS) $< -o $@
$(NAME): $(OBJS)
		@echo "$(CYAN)=========== Compilation $(LIBFT) ==========="
		make -C $(LIB_DIR)
		@echo "=========== DONE ==========$(RESET)"

		@echo "$(YELLOW)=========== Compilation $(NAME) ==========="
		$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIB_DIR)$(LIBFT) -o $(NAME)
		@echo "=========== DONE ==========$(RESET)"
$(NAME2): $(OBJS2)
		@echo "$(CYAN)=========== Compilation $(LIBFT) ==========="
		make -C $(LIB_DIR)
		@echo "=========== DONE ==========$(RESET)"

		@echo "$(YELLOW)=========== Compilation $(NAME2) ==========="
		$(CC) $(CFLAGS) $(OBJS2) $(LFLAGS) $(LIB_DIR)$(LIBFT) -o $(NAME2)
		@echo "=========== DONE ==========$(RESET)"
clean:
		@echo "$(PINK)========== CLEAN =========="
		$(RM) $(OBJ_DIR) $(OBJ_DIR2)
		$(RM) $(OBJS) $(OBJS2)
		make -C $(LIB_DIR) clean
		@echo "$(PINK)=========== DONE ===========$(RESET)"
fclean: clean
		@echo "$(RED)========== FCLEAN =========="
		$(RM) $(NAME) $(NAME2)
		make -C $(LIB_DIR) fclean
		@echo "$(RED)=========== DONE ===========$(RESET)"
bonus: all
re: fclean all