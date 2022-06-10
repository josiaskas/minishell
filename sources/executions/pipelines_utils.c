//
// Created by Josias Mutshaila kasongo on 2022-06-10.
//

#include "pipelines.h"

void    set_shell_error(t_shell_parser *parser, char *msg, int code)
{
    free(parser->error_msg);
    parser->error_msg = ft_strdup(msg);
    parser->status = code;
}