#ifndef BUILTINS_H
# define BUILTINS_H
# include "parser.h"

int	exit_builtin_cmd(t_shell *shell, t_command *cmd);
int	cd_builtin_cmd(t_shell *shell, t_command *cmd);
int	pwd_builtin_cmd(t_shell *shell, t_command *cmd);
int	echo_builtin_cmd(t_shell *shell, t_command *cmd);
int	env_builtin_cmd(t_shell *shell, t_command *cmd);
int	export_cmd_builtin(t_shell *shell, t_command *cmd);
int	unset_cmd_builtin(t_shell *shell, t_command *cmd);
#endif //BUILTINS_H
