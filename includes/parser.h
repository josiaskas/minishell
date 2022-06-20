/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:21:55 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/20 17:36:46 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "tokenizer.h"
# include "lexer.h"

typedef enum e_cmd_cond_type {
	e_cond_none,
	e_cond_and,
	e_cond_or,
}	t_cmd_cond_type;

typedef enum e_cmd_state {
	e_cmd_error,
	e_cmd_waiting,
	e_cmd_executed,
	e_cmd_paused,
	e_cmd_running,
}	t_cmd_state;

typedef enum e_cmd_internal {
	e_cmd_intern_echo,
	e_cmd_intern_cd,
	e_cmd_intern_pwd,
	e_cmd_intern_export,
	e_cmd_intern_unset,
	e_cmd_intern_env,
	e_cmd_intern_exit,
}	t_cmd_internal;

typedef struct s_redirection {
	int					fd;
	t_redirection_type	type;
	char				*filename;
}	t_redirection;

typedef struct s_command {
	pid_t				id;
	char				*cmd;
	t_array				*arguments;
	t_array				*env;
	t_array				*redirections;
	int					fd[3];
	t_cmd_cond_type		condition;
	int					shell_level;
	t_cmd_state			state;
	struct s_command	*pipe;
	struct s_command	*next;
	bool				is_internal;
	t_cmd_internal		internal_cmd;
	int					status;
	char				*error_msg;
	size_t				cursor;
}	t_command;

typedef struct s_shell {
	t_command	*commands_list;
	bool		syntax_error;
	bool		is_parent;
	char		*error_msg;
	int			status;
	int			pipes_len;
}	t_shell;

t_shell		*parse_shell_line(char *sentence);

t_command	*build_parse_cmd(t_array *lexer, size_t cursor);

void		check_internal_cmd(t_command *command);

bool		check_p_err(t_array *lex, t_shell *parser, size_t i, char *msg);

char		*get_red_filename(size_t i, t_array *lexer, t_command *cmd);

size_t		build_pipe_cmd(t_command *cmd, t_array *lexer, size_t cursor);

#endif
