/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:03:52 by anachat           #+#    #+#             */
/*   Updated: 2024/12/05 16:39:54 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_next_line(int fd)
{
	static char	*rema;
	ssize_t		bytes_read;
	char		*buffer;
	char		*line;

	if (check(fd) == -1 || allocate(&buffer) == -1)
		return (free(rema), rema = NULL, NULL);
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(rema), free(buffer), rema = NULL, buffer = NULL, NULL);
		buffer[bytes_read] = '\0';
		rema = ft_strjoin(rema, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
	line = set_line(rema);
	if (!line)
		return (free(rema), rema = NULL, NULL);
	rema = get_new_remainder(rema);
	return (line);
}
