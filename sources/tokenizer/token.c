/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:50:24 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/19 02:16:43 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// build the string token and escape char
static void	ft_str_tok(t_token *tok, char *str, size_t cursor, size_t len)
{
	char	*word;

	tok->type = e_token_text;
	tok->start_pos = cursor;
	word = NULL;
	while (cursor < len)
	{
		if (ft_isspace(str[cursor]) || ft_is_special_shell_char(str[cursor]))
			break ;
		else
			word = ft_concat_char(word, str[cursor]);
		cursor++;
	}
	tok->value = word;
	tok->end_pos = cursor;
}

// build shell special token and EOF token
static void	ft_sp_tok(t_token *token, char *sentence, size_t cursor)
{
	int	t;

	t = token->type;
	token->start_pos = cursor;
	token->end_pos = cursor;
	if (t == e_token_eof)
	{
		token->value = NULL;
		return ;
	}
	else
		token->value = ft_concat_char(NULL, sentence[cursor]);
	token->end_pos = cursor + 1;
}

/*
* Build s token by receiving the type and the lexical anylizer (tokenizer)
* Return a t_token*
* Push inside the stack the token created or pop and push a complex token eg: '||'
*/
t_token	*build_token(t_token_type t, t_tokeniser *lex, size_t cursor)
{
	t_token			*token;
	t_token			*last_tok;
	t_token_type	new_type;

		token = (t_token *)ft_calloc(1, sizeof(t_token));
	token->end_pos = cursor;
	token->type = t;
	if (t == e_token_text)
		ft_str_tok(token, lex->sentence, cursor, lex->len);
	else
	{
		new_type = ft_check_double_t(t, lex, cursor);
		if (new_type != 0)
		{
			last_tok = (t_token *)pop(lex->tokens);
			token->type = new_type;
			custom_tok(token, last_tok, cursor, lex->sentence);
		}
		else
			ft_sp_tok(token, lex->sentence, cursor);
	}
	lex->cursor = token->end_pos;
	push(lex->tokens, token);
	return (token);
}

static t_token	*spec_suite(t_tokeniser *lex, size_t cursor, char c)
{
	if (c == '<')
		return (build_token(e_token_less, lex, cursor));
	else if (c == '>')
		return (build_token(e_token_greater, lex, cursor));
	else if (c == '*')
		return (build_token(e_token_wildcard, lex, cursor));
	else if (c == '~')
		return (build_token(e_token_tilde, lex, cursor));
	else if (c == '=')
		return (build_token(e_token_equal, lex, cursor));
	else if (c == '#')
		return (build_token(e_token_hashtag, lex, cursor));
	else if (c == '{')
		return (build_token(e_token_left_curl, lex, cursor));
	else if (c == '}')
		return (build_token(e_token_right_curl, lex, cursor));
	else
		return (build_token(e_token_text, lex, cursor));
}

// check special char of the shell and build token or else a simple txt token
t_token	*build_spec_t(t_tokeniser *lex, size_t cursor, char c)
{
	if (c == 39)
		return (build_token(e_token_quote, lex, cursor));
	else if (c == 92)
		return (build_token(e_token_escape, lex, cursor));
	else if (c == 34)
		return (build_token(e_token_dquote, lex, cursor));
	else if (c == '$')
		return (build_token(e_token_dollar, lex, cursor));
	else if (c == '|')
		return (build_token(e_token_pipe, lex, cursor));
	else if (c == '&')
		return (build_token(e_token_and, lex, cursor));
	else if (c == ';')
		return (build_token(e_token_semicolon, lex, cursor));
	else if (c == '(')
		return (build_token(e_token_left_paren, lex, cursor));
	else if (c == ')')
		return (build_token(e_token_right_paren, lex, cursor));
	else
		return (spec_suite(lex, cursor, c));
}