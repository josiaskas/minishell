/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:08:50 by jkasongo          #+#    #+#             */
/*   Updated: 2022/05/11 15:34:43 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
# include "tokenizer.h"

typedef enum e_lex_type {
	e_lex_literal,
	e_lex_pipe,
	e_lex_keyword,
	e_lex_redirection,
	e_lex_quote_error,
	e_lex_redirection_error,
	e_lex_pipe_error,
}	t_lex_type;

typedef enum e_redirection_type {
	e_redirection_input,
	e_redirection_output,
	e_redirection_append_out,
	e_redirection_heredoc,
	e_redirection_here_string,
}	t_redirection_type;

typedef struct s_lex_token {
	t_lex_type			type;
	char				*value;
	t_redirection_type	r_type;
	int					fd;
}	t_lex_token;

size_t	analyse_lit(t_array *tokens, t_token *tok, size_t i, t_array *lex);

size_t	a_quote_t(t_array *toks, t_token *tok, size_t i, t_lex_token *lex_tok);

size_t	a_dquote_t(t_array *toks, t_token *tok, size_t i, t_lex_token *lex_tok);

size_t	a_var_t(t_token *tok, size_t i, t_lex_token *lex_tok);

size_t	analyse_redirection(t_token *token, size_t cursor, t_array *lex);

t_array	*run_simple_lexer(t_array *tokens);

void	destroy_lexer(t_array *lexer);

bool	is_minishell_redir(t_token *token);

int		lex_get_status_value(int is_reset);

bool	check_if_is_literal(t_token *tok);

bool	is_close_t_s(t_array *tokens, t_token *token, size_t i);
#endif
