/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:03:52 by anachat           #+#    #+#             */
/*   Updated: 2024/11/28 11:32:54 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t get_nl_index(char *str)
{
	ssize_t	i;

	if(!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if(str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		buffer[BUFFER_SIZE + 1];
	// char		*buffer;
	char		*line = NULL;
	ssize_t			i;
	ssize_t bytes_read;
	char *tmp = NULL;

	// buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while((bytes_read = read(fd, buffer, BUFFER_SIZE)) >= 0 || str != NULL)
	{
		// printf(YELLOW "==> [bytes_read]: '%zd'  |  ==> [buffer]: '%s'  |  [str]: '%s'\n" RESET, bytes_read, buffer, str);
		if(bytes_read == 0 && str && *str == '\0')
			return (NULL);
		buffer[bytes_read] = '\0';
		str = ft_strjoin(str, buffer);
		i = get_nl_index(str);
		// printf(YELLOW "==> [buffer]: '%s'  |  [str]: '%s'\n" RESET, buffer, str);
		if(i != -1)
		{
			// printf("[i = %zd]\n", i);
			// get the first part + \n
			line = strndup(str, i + 1);
			// get the last part after \n
			tmp = strdup(str + i + 1);
			free(str);
			str = tmp;
			free(tmp);
			// printf(RED "str: %s\n" RESET, str);
			// printf(RED "bytes read: %zd\n" RESET, bytes_read);
			return (line);
		}
		if (bytes_read <= 0 && str != NULL && *str != '\0')
		{
			line = strdup(str);
			free(str);
			str = NULL;
			return (line);
		}
	}
	free(tmp);
	free(str);
	free(line);
	return (NULL);
}
