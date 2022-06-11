/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:08:13 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 19:22:12 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"


static char	*quick_concatenate(t_token *tok, char *old_value)
{
	char	*temp;

	temp = NULL;
	if (tok->meta)
	{
		temp = ft_strjoin(old_value, tok->meta);
		free(old_value);
		old_value = temp;
	}
	temp = ft_strjoin(old_value, tok->value);
	free(old_value);
	old_value = temp;
	return (old_value);
}

static char	*get_variable_value_from_tok(t_token *tok)
{
	t_dic_node	*dic;
	char		*value;

	dic = NULL;
	value = NULL;
	if (tok->value)
	{
		if (ft_strncmp(tok->value, "?", ft_strlen(tok->value)) == 0)
			value = ft_itoa(lex_get_status_value(2));
		else
		{
			dic = ft_elem_dic(g_shell.env, tok->value);
			if (dic)
				value = ft_strdup((char *)dic->content);
		}
	}
	return (value);
}

// push the literal token build inside single quote, return the cursor
size_t	a_quote(t_array *tokens, t_token *tok, size_t i, t_array *lex)
{
	t_lex_token	*lex_tok;

	lex_tok = (t_lex_token *)ft_calloc(1, sizeof(t_lex_token));
	tok = (t_token *)ft_get_elem(tokens, ++i);
	while ((tok->type != e_token_quote) && (tok->type != e_token_eof))
	{
		lex_tok->value = quick_concatenate(tok, lex_tok->value);
		tok = (t_token *)ft_get_elem(tokens, ++i);
	}
	if (tok->type == e_token_eof)
		lex_tok->type = e_lex_quote_error;
	else
		i++;
	ft_push(lex, lex_tok);
	return (i);
}

// push the literal token build inside double quote, return the cursor
size_t	a_dquote(t_array *tokens, t_token *tok, size_t i, t_array *lex)
{
	t_lex_token	*lex_tok;
	char		*temp;

	lex_tok = (t_lex_token *)ft_calloc(1, sizeof(t_lex_token));
	tok = (t_token *)ft_get_elem(tokens, ++i);
	lex_tok->value = NULL;
	while ((tok->type != e_token_dquote) && (tok->type != e_token_eof))
	{
		if (tok->type == e_token_variable)
		{
			temp = ft_strjoin(lex_tok->value, get_variable_value_from_tok(tok));
			free(lex_tok->value);
			lex_tok->value = temp;
		}
		else
			lex_tok->value = quick_concatenate(tok, lex_tok->value);
		tok = (t_token *)ft_get_elem(tokens, ++i);
	}
	if (tok->type == e_token_eof)
		lex_tok->type = e_lex_quote_error;
	else
		i++;
	ft_push(lex, lex_tok);
	return (i);
}

// push inside t_array *lex the value of the variable (tok->value) return i++;
size_t	analyse_var(t_token *tok, size_t i, t_array *lex)
{
	t_lex_token	*lex_tok;

	if (tok->type == e_token_variable)
	{
		lex_tok = (t_lex_token *)ft_calloc(1, sizeof(t_lex_token));
		lex_tok->type = e_lex_literal;
		lex_tok->value = get_variable_value_from_tok(tok);
		ft_push(lex, lex_tok);
		i++;
	}
	return (i);
}

