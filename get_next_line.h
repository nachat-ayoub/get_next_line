/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:36:48 by anachat           #+#    #+#             */
/*   Updated: 2024/11/30 10:19:42 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GREEN
# define GREEN "\033[32m"
#endif
#ifndef RED
# define RED "\033[31m"
#endif
#ifndef YELLOW
# define YELLOW "\033[33m"
#endif
#ifndef BLUE
# define BLUE    "\033[34m"
#endif
#ifndef MAGENTA
# define MAGENTA "\033[35m"
#endif
#ifndef CYAN
# define CYAN    "\033[36m"
#endif
#ifndef RESET
# define RESET "\033[0m"
#endif

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

char	*get_next_line(int fd);
size_t	ft_strlen(char *str);
char	*ft_strchr(char *str, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);

#endif
