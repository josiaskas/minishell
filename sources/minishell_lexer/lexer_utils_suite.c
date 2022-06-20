
#include "../../includes/lexer.h"
#include "../../includes/minishell.h"

/*
 * return true if token is a redirection token
 */
bool	is_minishell_redir(t_token *token)
{
	if (token)
	{
		if ((token->type == e_token_less)
			|| (token->type == e_token_greater)
			|| (token->type == e_token_heredoc_right)
			|| (token->type == e_token_heredoc_left)
			|| (token->type == e_token_herestr))
			return (true);
	}
	return (false);
}

/*
 * return the g_shell.satus, but can be reset to 0
 * 128 to reset every call after that return 0
 * 1 to reset return to real g_shell.status after that call
 * other number to not influence
 */
int	lex_get_status_value(int is_reset)
{
	static int	is_to_zero = 0;
	int			value;

	value = 0;
	if (is_reset == 128)
		is_to_zero = 1;
	else if (is_reset == 1)
		is_to_zero = 0;

	if (is_to_zero == 1)
		value = 0;
	else
		value = g_shell.status;
	return (value);
}

/*
 * Push inside lex an error token if token->type is e_token_herestr
 */
size_t	make_redirection_error(t_token *token, size_t cursor, t_array *lex)
{
	t_lex_token	*lex_tok;

	if (token->type == e_token_herestr)
	{
		lex_tok = (t_lex_token *)ft_calloc(1, sizeof(t_lex_token));
		lex_tok->type = e_lex_redirection_error;
		lex_tok->value = NULL;
		ft_push(lex, lex_tok);
		cursor++;
	}
	return (cursor);
}

void	destroy_lexer(t_array *lexer)
{
	t_lex_token	*content;

	if (!lexer)
		return ;
	while (lexer->length)
	{
		content = (t_lex_token *)ft_pop(lexer);
		free(content->value);
		free(content);
	}
	free(lexer);
	lexer = NULL;
}
