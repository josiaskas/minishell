# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 18:37:04 by jkasongo          #+#    #+#              #
#    Updated: 2022/03/05 19:20:16 by jkasongo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes

#source
SRCS_DIR = sources/
SRCS = main.c

SRCS_PREFIXED = $(addprefix $(SRCS_DIR), $(SRCS))

#objsm
OBJS = $(SRCS_PREFIXED:.c=.o)

all : $(NAME)

%.o: %.c ./includes/minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@$(MAKE) re -C ./libft
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)
	@echo $(NAME) est construit

clean :
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJS)
	@echo cleaning

fclean : clean
	@$(MAKE) fclean -C ./libft
	@rm -rf $(NAME)
	@echo "full clean"

re : fclean all

launch :all
	./minishell

.PHONY	: all clean fclean re help launch
