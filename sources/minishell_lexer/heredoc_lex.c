/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_lex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:02:47 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/17 20:36:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

size_t	all_lit(t_array *tokens, t_token *tok, size_t i, t_array *lex)
{
	t_lex_token	*lex_tok;
	char		*temp;

	lex_tok = (t_lex_token *)ft_calloc(1, sizeof(t_lex_token));
	lex_tok->type = e_lex_literal;
	lex_tok->value = NULL;
	while ((tok->type != e_token_quote)
		&& (tok->type != e_token_dquote)
		&& (tok->type != e_token_variable)
		&& (tok->type != e_token_eof))
	{
		temp = ft_strjoin(lex_tok->value, tok->value);
		free(lex_tok->value);
		lex_tok->value = temp;
		i++;
		tok = (t_token *)ft_get_elem(tokens, i);
	}
	ft_push(lex, lex_tok);
	return (i);
}

size_t	get_hd_a(t_array *tokens, t_token *tok, size_t i, t_array *lex)
{
	size_t	cursor;

	cursor = i;
	if (tok->type == e_token_quote)
		cursor = a_quote(tokens, tok, cursor, lex);
	else if (tok->type == e_token_dquote)
		cursor = a_dquote(tokens, tok, cursor, lex);
	else if (tok->type == e_token_variable)
		cursor = analyse_var(tok, cursor, lex);
	else
		cursor = all_lit(tokens, tok, cursor, lex);
	return (cursor);
}

static t_array	*heredoc_lexer(char *sentence)
{
	t_tokeniser	*tokenizer;
	t_token		*token;
	t_array		*lexer;
	size_t		i;

	lexer = ft_new_array();
	tokenizer = init_tokenizer(sentence);
	token = get_next_token(tokenizer);
	while (token->type != e_token_eof)
		token = get_next_token(tokenizer);
	i = 0;
	token = (t_token *)ft_get_elem(tokenizer->tokens, i);
	while (token->type != e_token_eof)
	{
		i = get_hd_a(tokenizer->tokens, token, i, lexer);
		token = (t_token *)ft_get_elem(tokenizer->tokens, i);
	}
	destroy_tokinizer(tokenizer);
	return (lexer);
}

void	print_heredoc_lex(char *sentence, int write_pipe)
{
	t_array		*lexer;
	size_t		cursor;
	t_lex_token	*lex_tok;

	lexer = heredoc_lexer(sentence);
	cursor = 0;
	while (cursor < lexer->length)
	{
		lex_tok = (t_lex_token *)ft_get_elem(lexer, cursor);
		if (lex_tok)
			ft_putstr_fd(lex_tok->value, write_pipe);
		cursor++;
	}
	write(write_pipe, "\n", 1);
	destroy_lexer(lexer);
}