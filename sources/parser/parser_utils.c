/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:09:34 by jkasongo          #+#    #+#             */
/*   Updated: 2022/05/04 21:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 * Check if the command is an internal command
 * set command->is_internal
 * set command->internal_cmd value
 */
void    check_internal_cmd(t_command *command)
{
   char *list;
   char **internals;
   int  i;

   if (!command)
       return;
   list = "echo cd pwd export unset env exit";
   internals = ft_split(list, ' ');
   i = 0;
   while (internals[i] != NULL)
   {
       if (!ft_strncmp(command->cmd, internals[i], ft_strlen(command->cmd)))
       {
            command->is_internal = true;
            command->internal_cmd = i;
       }
       i++;
   }
}

/*
 * Check parse errors and print error
 * print an error if exit on STDERR_FILENO
 * return boolean (true) if no error (false) if found errors;
 */
bool    check_parse_errors(t_array  *lexer)
{
    size_t  i;
    t_lex_token *token;

    if (!lexer)
        return(false);
    i = 0;
    while (i < lexer->length)
    {
        token = (t_lex_token *)ft_get_elem(lexer, i++);
        if (token->type == e_lex_pipe_error)
        {
            ft_putstr_fd(
                    "syntax error || (OR token) are not currently treated\n",
                    STDERR_FILENO);
            return (false);
        }
        else if (token->type == e_lex_quote_error)
        {
            ft_putstr_fd("syntax error Quote error\n",STDERR_FILENO);
            return (false);
        }
    }
    return (true);
}

char    *get_red_filename(size_t cursor, t_array *lexer)
{
    t_lex_token *next_token;
    char        *filename;

    filename  = NULL;
    next_token = (t_lex_token *)ft_get_elem(lexer, cursor + 1);
    if ((!next_token) || (next_token->type != e_lex_literal))
    {
        ft_putstr_fd("syntax error unexpected token\n",STDERR_FILENO);
        return (NULL);
    }
    filename = ft_strdup(next_token->value);
    return (filename);
}