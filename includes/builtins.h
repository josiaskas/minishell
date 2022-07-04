/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:08:50 by jkasongo          #+#    #+#             */
/*   Updated: 2022/05/11 15:34:43 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "parser.h"

int		exit_builtin_cmd(t_shell *shell, t_command *cmd);
int		cd_builtin_cmd(t_shell *shell, t_command *cmd);
int		pwd_builtin_cmd(t_shell *shell, t_command *cmd);
int		echo_builtin_cmd(t_shell *shell, t_command *cmd);
int		env_builtin_cmd(t_shell *shell, t_command *cmd);
int		export_cmd_builtin(t_shell *shell, t_command *cmd);
int		unset_cmd_builtin(t_shell *shell, t_command *cmd);
char	*ft_get_env_varname(const char *env_line);
void	ft_print_env_variables(t_command *cmd);
void	ft_print_env_variables_with_declare(t_command *cmd);
bool	is_valid_varname_id(char *var_name);
char	**get_env_array_with_eq(t_command *command);
#endif //BUILTINS_H
