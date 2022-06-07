/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:52:09 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/07 14:52:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipelines.h"


/*
 * take parser result and makes redirection, pipes and fork for execution
 * return a code and set g_shell.status
 */
int run_pipeline(t_shell_parser *parser)
{
    int code;

    code = 0;
    if (parser->syntax_error)
    {
        ft_putstr_fd(parser->error_msg, STDERR_FILENO);
        g_shell.status = 258;
        return (258);
    }
    g_shell.status = 0;
    return (code);
}
