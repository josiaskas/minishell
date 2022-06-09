/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:56:42 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/07 15:56:53 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINES_H
# define PIPELINES_H
# include "parser.h"
# include "minishell.h"

int run_pipeline(t_shell_parser *parser);
void    destroy_redirections(t_array *redirections);
#endif //PIPELINES_H
