/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   -get_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:03:52 by anachat           #+#    #+#             */
/*   Updated: 2024/12/02 18:28:41 by anachat          ###   ########.fr       */
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
 
static char *set_line(char **line)
{
    char *remainder;
    char *tmp;
    ssize_t i = 0;

    if (!line || !*line)
        return (NULL);
    while ((*line)[i] != '\n' && (*line)[i] != '\0')
        i++;
    if ((*line)[i] == '\0' || (*line)[1] == '\0')
        return (NULL);
    remainder = ft_substr(*line, i + 1, ft_strlen(*line) - i);
    if (!remainder)
        return (NULL); // Allocation failure
    if (*remainder == '\0')
    {
        free(remainder);
        remainder = NULL;
    }
    tmp = ft_substr(*line, 0, i + 1);
    if (!tmp)
        return (free(remainder), NULL); // Ensure `remainder` is freed
    free(*line);
    *line = tmp;
    return (remainder);
}

static char *fill_line_buffer(int fd, char *remainder, char *buffer)
{
    ssize_t bytes_read;
    char *tmp;

    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer, (size_t)BUFFER_SIZE);
        if (bytes_read == -1)
            return (NULL); // Return NULL; do not free `remainder`
        else if (bytes_read == 0)
            break;
        buffer[bytes_read] = '\0';
        if (!remainder)
            remainder = ft_strdup("");
        if (!remainder)
            return (NULL);
        tmp = remainder;
        remainder = ft_strjoin(tmp, buffer);
        if (!remainder) // Return NULL if `ft_strjoin` fails
            return (NULL);
        free(tmp); // Free old `remainder` only after successful `ft_strjoin`
        if (ft_strchr(remainder, '\n'))
            break;
    }
    return (remainder);
}


char *get_next_line(int fd)
{
    static char *remainder = NULL;
    char *buffer;
    char *line;

    buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer || fd < 0 || (size_t)BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd > OPEN_MAX)
    {
        if (buffer)
            free(buffer);
        if (remainder)
            free(remainder), remainder = NULL;
        return (NULL);
    }
    line = fill_line_buffer(fd, remainder, buffer);
    free(buffer);
	if (!line)
	{
		if (remainder)
		{
			free(remainder);
			remainder = NULL;
		}
		return (NULL);
	}
    remainder = set_line(&line);
    return (line);
}

