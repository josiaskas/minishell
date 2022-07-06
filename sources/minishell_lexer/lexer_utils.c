/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:08:13 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/25 16:34:45 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

void	lex_concate_tok_dquote_util(t_lex_token *lex_tok, t_token *tok);

// concatenate by toking the value inside a tok (metas included)
char	*quick_concatenate(t_token *tok, char *old_value)
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

char	*get_variable_value_from_tok(t_token *tok)
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

/*
 * Add to literal the value inside single quote
 * concatenate inside lex_tok->value
 * or set lex_tok->type to error
 */
size_t	a_quote_t(t_array *toks, t_token *tok, size_t i, t_lex_token *lex_tok)
{
	tok = (t_token *)ft_get_elem(toks, ++i);
	while ((tok->type != e_token_quote) && (tok->type != e_token_eof))
	{
		lex_tok->value = quick_concatenate(tok, lex_tok->value);
		tok = (t_token *)ft_get_elem(toks, ++i);
	}
	if (tok->type == e_token_eof)
		lex_tok->type = e_lex_quote_error;
	else
		i++;
	if (!lex_tok->value)
		lex_tok->value = ft_strdup("");
	return (i);
}

/*
 * Add to literal the value inside double quote
 * concatenate inside lex_tok->value
 * or set lex_tok->type to error
 */
size_t	a_dquote_t(t_array *toks, t_token *tok, size_t i, t_lex_token *lex_tok)
{
	tok = (t_token *)ft_get_elem(toks, ++i);
	while ((tok->type != e_token_dquote) && (tok->type != e_token_eof))
	{
		lex_concate_tok_dquote_util(lex_tok, tok);
		tok = (t_token *)ft_get_elem(toks, ++i);
	}
	if (tok->type == e_token_eof)
		lex_tok->type = e_lex_quote_error;
	else
		i++;
	if (!lex_tok->value)
		lex_tok->value = ft_strdup("");
	return (i);
}

/*
 * Add to literal the value inside var
 * concatenate inside lex_tok->value
 * or set lex_tok->type to error
 */
size_t	a_var_t(t_token *tok, size_t i, t_lex_token *lex_tok)
{
	char	*tmp;
	char	*var;

	tmp = NULL;
	if (tok->type == e_token_variable)
	{
		var = get_variable_value_from_tok(tok);
		tmp = ft_strjoin(lex_tok->value, var);
		free(lex_tok->value);
		free(var);
		lex_tok->value = tmp;
		i++;
	}
	return (i);
}
