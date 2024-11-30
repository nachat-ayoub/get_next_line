/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:03:52 by anachat           #+#    #+#             */
/*   Updated: 2024/11/30 10:28:29 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line_buffer(int fd, char *remainder, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		if(!remainder)
			remainder = ft_strdup("");
		tmp = ft_strjoin(remainder, buffer);
		if (!tmp)
			return (NULL);
		free(remainder);
		remainder = tmp;
		tmp = NULL;
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	if (bytes_read == -1)
	{
		free(remainder);
		return (NULL);
	}
	return (remainder);
}


static char	*set_line(char *line)
{
	char	*remainder;
	size_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if(line[i] == '\0' || line[1] == '\0')
		return (NULL);
	remainder = ft_substr(line, i + 1, ft_strlen(line) - i);
	// printf(RED "[remainder]: %s\n" RESET, remainder);
	if(remainder && remainder[0] == '\0')
	{
		free(remainder);
		remainder = NULL; 
	}
	line[i + 1] = '\0';
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;

    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if ((fd < 0) || (BUFFER_SIZE <= 0) || (read(fd, 0, 0) < 0) || fd > OPEN_MAX)
	{
		free(buffer);
		free(remainder);
		buffer = NULL;
		remainder = NULL;
		printf("Here\n");
		return (NULL);
	}
	if(!buffer)
		return (NULL);
	line = fill_line_buffer(fd, remainder, buffer);
	free(buffer);
	buffer = NULL;
	if(!line)
		return (free(remainder), NULL);
	remainder = set_line(line);
	return (line);
}
