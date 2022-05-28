# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 18:37:04 by jkasongo          #+#    #+#              #
#    Updated: 2022/05/11 11:09:51 by jkasongo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES_DIR = includes/

#source
SRCS_DIR = sources/
PARSER_SRC = parser.c parser_utils.c
PARSER_PREFIXED = $(addprefix parser/, $(PARSER_SRC))
TOKENIZER_SRC = tokenizer.c token.c token_special.c token_utils.c
TOKENIZER_PREFIXED = $(addprefix tokenizer/, $(TOKENIZER_SRC))

#lexer normal
LEXER_SRC = lexer.c lexer_utils.c
LEXER_PREFIXED = $(addprefix minishell_lexer/, $(LEXER_SRC))
#lexer bonus

#lexer full shell
STATUS_SRC = bar.c environement.c
STATUS_PREFIXED = $(addprefix status/, $(STATUS_SRC))

SRCS = main.c prompt.c $(PARSER_PREFIXED) $(TOKENIZER_PREFIXED) $(STATUS_PREFIXED) $(LEXER_PREFIXED)
SRCS_PREFIXED = $(addprefix $(SRCS_DIR), $(SRCS))

#includes
INCLUDES_FILES = minishell.h tokenizer.h status.h parser.h lexer.h
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
	@$(CC) $(CFLAGS) $(OBJS_PREFIXED) -lft -L./libft -lreadline -o $(NAME)
	@echo $(NAME) est construit

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@mkdir $(OBJS_DIR)/parser
	@mkdir $(OBJS_DIR)/tokenizer
	@mkdir $(OBJS_DIR)/minishell_lexer
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
