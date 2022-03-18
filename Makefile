# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 18:37:04 by jkasongo          #+#    #+#              #
#    Updated: 2022/03/18 18:08:52 by jkasongo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES_DIR = includes/

#source
SRCS_DIR = sources/
SRCS = main.c prompt.c parser/parser.c parser/parser_utils.c parser/tokenizer.c \
		parser/token.c status/bar.c

SRCS_PREFIXED = $(addprefix $(SRCS_DIR), $(SRCS))

#includes
INCLUDES_FILES = tokenizer.h parser.h minishell.h status.h
INCLUDES_PREFIXED = $(addprefix $(INCLUDES_DIR), $(INCLUDES_FILES))

#objsm
OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
OBJECTS_LIST = $(patsubst %.c, %.o, $(SRCS))
#style
GREEN = \033[0;32m
RED = \033[0;31m
RESET_COLOR = \033[0m

.PHONY	: all clean fclean re help launch

all : $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS_PREFIXED)
	@$(MAKE) re -C ./libft
	@$(CC) $(CFLAGS) $(OBJS_PREFIXED) -L./libft -lft -lreadline -o $(NAME)
	@echo $(NAME) est construit

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@mkdir $(OBJS_DIR)/parser
	@mkdir $(OBJS_DIR)/status

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(INCLUDES_PREFIXED)
	$(CC) $(CFLAGS) -I./$(INCLUDES_DIR) -c $< -o $@

clean :
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJS_DIR)
	@echo 'cleaning objs'

fclean : clean
	@$(MAKE) fclean -C ./libft
	@rm -rf $(NAME)
	@echo "$(GREEN)full clean$(RESET_COLOR)"

re : fclean all

launch :all
	./minishell

help :
	@echo ' all clean fclean re launch help minishell'
