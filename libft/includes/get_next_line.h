/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 01:30:29 by jkasongo          #+#    #+#             */
/*   Updated: 2021/09/22 01:47:24 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# include "../libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# define GET_NEXT_LINE_H
# ifndef FILE_BUFFER_SIZE
#  define FILE_BUFFER_SIZE 151
# endif
# ifndef MAX_FD
#  define MAX_FD 65535
# endif

// get line by line of a file
int	get_next_line(int fd, char **line);

#endif
