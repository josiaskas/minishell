/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:52:57 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/13 20:04:29 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_tokeniser	*init_tokenizer(char *sentence)
{
	t_tokeniser	*lexical_int;
	t_stack		*tokens;

	lexical_int = NULL;
	tokens = NULL;
	lexical_int = (t_tokeniser *)ft_calloc(1, sizeof(t_tokeniser));
	if (!lexical_int)
		return (NULL);
	lexical_int->cursor = 0;
	lexical_int->sentence = sentence;
	lexical_int->len = ft_strlen(sentence);
	tokens = create_stack();
	if (!tokens)
		return (NULL);
	lexical_int->tokens = tokens;
	return (lexical_int);
}

// build token and poush them in the stack
static t_token	*build_token(t_token_type t, t_tokeniser *lex, size_t cursor)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	token->end_pos = cursor;
	token->type = t;
	if (t == e_token_text)
		ft_str_tok(token, lex->sentence, cursor, lex->len);
	else if (t == e_token_logic_op)
		ft_op_tok(token, lex->sentence, cursor);
	else
		ft_sp_tok(token, lex->sentence, cursor);
	lex->cursor = token->end_pos;
	push(lex->tokens, token);
	return (token);
}

static t_token *spec_s(t_tokeniser *lex, size_t cursor, char c, char next_c)
{
	if (c == '<' && next_c == '<')
		return (build_token(e_token_less_less, lex, cursor));
	else if (c == '<')
		return (build_token(e_token_less, lex, cursor));
	else if (c == '>' && next_c == '>')
		return (build_token(e_token_greater_greater, lex, cursor));
	else if (c == '>')
		return (build_token(e_token_greater, lex, cursor));
	else if (c == '*')
		return (build_token(e_token_wildcard, lex, cursor));
	else
		return (build_token(e_token_text, lex, cursor));
}

// check special char of the shell and build token or else a simple txt token
static t_token	*spec_t(t_tokeniser *lex, size_t cursor, char c, char next_c)
{
	if (c == 39)
		return (build_token(e_token_quote, lex, cursor));
	else if (c == 34)
		return (build_token(e_token_dquote, lex, cursor));
	else if (c == '$')
		return (build_token(e_token_dollar, lex, cursor));
	if (c == '|' && next_c != '|')
		return (build_token(e_token_pipe, lex, cursor));
	if (c == '&' && next_c != '&')
		return (build_token(e_token_and, lex, cursor));
	if ((c == '&' && next_c == '&') || (c == '|' && next_c == '|'))
		return (build_token(e_token_logic_op, lex, cursor));
	else if (c == ';')
		return (build_token(e_token_semicolon, lex, cursor));
	else if (c == '(')
		return (build_token(e_token_left_paren, lex, cursor));
	else if (c == ')')
		return (build_token(e_token_left_paren, lex, cursor));
	else
		return (spec_s(lex, cursor, c, next_c));
}

// build and return the next token on demand
t_token	*get_next_token(t_tokeniser *lexical)
{
	size_t	cursor;
	char	current;
	char	next_c;

	cursor = lexical->cursor;
	current = lexical->sentence[cursor];
	if (lexical->cursor >= lexical->len)
		return (build_token(e_token_eof, lexical, cursor));
	while (ft_isspace(current) && (current != 0))
	{
		cursor++;
		current = lexical->sentence[cursor];
	}
	next_c = lexical->sentence[cursor + 1];
	if (ft_is_special_shell_char(current))
		return (spec_t(lexical, cursor, current, next_c));
	else
		return (build_token(e_token_text, lexical, cursor));
}
