/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:03:52 by anachat           #+#    #+#             */
/*   Updated: 2024/12/05 16:41:03 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*set_line(char *remainder)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!remainder || *remainder == 0)
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	line = ft_substr(remainder, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

static char	*get_new_remainder(char *remainder)
{
	char	*new_remainder;
	size_t	i;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	new_remainder = ft_substr(remainder, i, ft_strlen(remainder));
	free(remainder);
	remainder = NULL;
	if (!new_remainder)
		return (NULL);
	return (new_remainder);
}

static int	check(int fd)
{
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (-1);
	return (1);
}

static int	allocate(char	**buffer)
{
	*buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!*buffer)
		return (-1);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*rem[OPEN_MAX];
	ssize_t		bytes_read;
	char		*buf;
	char		*line;

	if (check(fd) == -1 || allocate(&buf) == -1)
		return (free(rem[fd]), rem[fd] = NULL, NULL);
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(rem[fd]), free(buf), rem[fd] = NULL, buf = NULL, NULL);
		buf[bytes_read] = '\0';
		rem[fd] = ft_strjoin(rem[fd], buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	buf = NULL;
	line = set_line(rem[fd]);
	if (!line)
		return (free(rem[fd]), rem[fd] = NULL, NULL);
	rem[fd] = get_new_remainder(rem[fd]);
	return (line);
}
