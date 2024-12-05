/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:36:48 by anachat           #+#    #+#             */
/*   Updated: 2024/12/05 16:37:14 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_next_line(int fd);
size_t	ft_strlen(char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);

#endif