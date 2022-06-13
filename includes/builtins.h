#ifndef BUILTINS_H
# define BUILTINS_H
# include "parser.h"

int	exit_builtin_cmd(t_shell *shell, t_command *cmd);
int	cd_builtin_cmd(t_shell *shell, t_command *cmd);
int	jobs_builtin_cmd(t_shell *shell, t_command *cmd);
#endif //MINISHELL_BUILTINS_H
