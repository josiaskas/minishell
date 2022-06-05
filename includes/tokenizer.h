/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:55:54 by jkasongo          #+#    #+#             */
/*   Updated: 2022/05/10 19:14:24 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h"

typedef enum e_token_type
{
	e_token_escape,
	e_token_quote,
	e_token_dquote,
	e_token_dollar,
	e_token_wildcard,
	e_token_equal,
	e_token_tilde,
	e_token_pipe,
	e_token_semicolon,
	e_token_and,
	e_token_less,
	e_token_greater,
	e_token_left_paren,
	e_token_right_paren,
	e_token_left_curl,
	e_token_right_curl,
	e_token_text,
	e_token_number,
	e_token_space,
	e_token_hashtag,
	e_token_double_and,
	e_token_or,
	e_token_subst,
	e_token_heredoc_left,
	e_token_heredoc_right,
	e_token_herestr,
	e_token_variable,
	e_token_eof,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*meta;
	size_t			start_pos;
	size_t			end_pos;
}	t_token;

typedef struct s_tokinzer
{
	char	*sentence;
	size_t	len;
	size_t	cursor;
	t_array	*tokens;
}	t_tokeniser;

t_tokeniser	*init_tokenizer(char *sentence);
void		destroy_tokinizer(t_tokeniser *lexical);
t_token		*get_next_token(t_tokeniser *lexical);
t_token		*build_spec_t(t_tokeniser *lex, size_t cursor, char c);
t_token		*build_token(t_token_type t, t_tokeniser *lex, size_t cursor);

bool		ft_is_special_shell_char(char value);
char		*ft_concat_char(char *str, char c);
int			ft_check_double_t(int t, t_tokeniser *lex, size_t cursor);
void		custom_tok(t_token *curr, t_token *last, int cursor, char *str);
bool		ft_is_a_number(char *str);
char		*get_word_in_sentence(size_t cursor, char *str, size_t len);
#endif
