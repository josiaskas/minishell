/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:56:42 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 19:19:35 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINES_H
# define PIPELINES_H
# include "parser.h"
# include "minishell.h"

int		run_pipeline(t_shell *parser);
int		make_pipeline(t_shell *parser);
void	destroy_redirections(t_array *redirections);
void	set_shell_error(t_shell *parser, char *msg, int code);
void	close_all_pipes(int *pipes[], int len);

#endif //PIPELINES_H
