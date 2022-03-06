/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 01:36:49 by jkasongo          #+#    #+#             */
/*   Updated: 2021/09/22 01:45:29 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static char	*ft_strjoin_with_free(char *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*heap_p;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	heap_p = malloc(len1 + len2 + 1);
	if (!heap_p)
		return (0);
	ft_memmove(heap_p, s1, len1);
	ft_memmove((heap_p + len1), s2, len2);
	heap_p[len1 + len2] = 0;
	free(s1);
	return (heap_p);
}

static char	*read_file_data(int fd, char **line, int *readed)
{
	char	*endl;
	char	*tmp;
	char	buffer[FILE_BUFFER_SIZE + 1];
	char	*last_part;

	ft_bzero(buffer, (FILE_BUFFER_SIZE + 1));
	last_part = 0;
	while ((*readed) > 0)
	{
		tmp = *line;
		*line = ft_strjoin_with_free(tmp, buffer);
		endl = ft_strchr(*line, 10);
		if (endl)
		{
			tmp = ft_strndup(*line, (endl - *line));
			if (ft_strlen(endl) > 1)
				last_part = ft_strdup(endl + 1);
			free(*line);
			*line = tmp;
			return (last_part);
		}
		ft_bzero(buffer, (FILE_BUFFER_SIZE + 1));
		*readed = read(fd, buffer, FILE_BUFFER_SIZE);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*file[MAX_FD] = {0};
	int			readed;
	size_t		len;

	readed = 1;
	if ((fd < 0) || (!line) || (FILE_BUFFER_SIZE < 1)
		|| (read(fd, file, 0) < 0))
		return (-1);
	*line = 0;
	len = ft_strlen(file[fd]);
	if (len)
		*line = file[fd];
	file[fd] = 0;
	file[fd] = read_file_data(fd, line, &readed);
	if (readed > 1)
		return (1);
	return (readed);
}
