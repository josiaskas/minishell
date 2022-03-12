/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:55:54 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/12 13:40:46 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "parser.h"

typedef enum e_token_type
{
	e_token_pipe,
	e_token_semicolon,
	e_token_less,
	e_token_less_less,
	e_token_greater,
	e_token_greater_greater,
	e_token_or,
	e_token_and,
	e_token_and_and,
	e_token_wildcard,
	e_token_env_variable,
	e_token_eof,
	e_token_left_paren,
	e_token_right_paren,
	e_token_text,
	e_token_error,
	e_token_logic_op,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	size_t			start_pos;
	size_t			end_pos;
}	t_token;

typedef struct s_tokinzer
{
	char	*sentence;
	size_t	len;
	size_t	cursor;
	t_stack	*tokens;
}	t_tokeniser;

t_tokeniser	*init_tokenizer(char *sentence);
void		destroy_tokinizer(t_tokeniser *lexical);
t_token		*get_next_token(t_tokeniser *lexical);

void		ft_str_tok(t_token *tok, char *str, size_t cursor, size_t len);
void		ft_op_tok(t_token *tok, char *str, size_t cursor);
void		ft_sp_tok(t_token *tok, char *str, size_t cursor);
void		build_error_token(t_token *token, size_t cursor, int error);
bool		ft_is_special_shell_char(char value);
bool		ft_is_a_quote_char(char value);
char		*ft_concat_char(char *str, char c);

#endif
