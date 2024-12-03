/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:03:52 by anachat           #+#    #+#             */
/*   Updated: 2024/12/03 10:45:38 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	if (!s)
		return (NULL);
	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

static char	*set_line(char **line)
{
	char	*remainder;
	char	*tmp;
	ssize_t	i;

	i = 0;
	while ((*line)[i] != '\n' && (*line)[i] != '\0')
		i++;
	if ((*line)[i] == '\0' || (*line)[1] == '\0')
		return (NULL);
	remainder = ft_substr(*line, i + 1, ft_strlen(*line) - i);
	if (!remainder || *remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	tmp = ft_substr(*line, 0, i + 1);
	free(*line);
	*line = tmp;
	tmp = NULL;
	if(!tmp)
		return (NULL);
	return (remainder);
}

static char	*fill_line_buffer(int fd, char *remainder, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, ((size_t)BUFFER_SIZE));
		if (bytes_read == -1)
			return (free(remainder), NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!remainder)
			remainder = ft_strdup("");
		if (!remainder)
			return (NULL);
		tmp = remainder;
		remainder = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (!remainder)
			return (NULL);
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;

	buffer = malloc((((size_t)BUFFER_SIZE) + 1) * sizeof(char));
	if (!buffer || fd < 0 || (size_t)BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0
		|| fd > OPEN_MAX)
	{
		free(remainder);
		remainder = NULL;
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, remainder, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (free(remainder), NULL);
	remainder = set_line(&line);
	return (line);
}
