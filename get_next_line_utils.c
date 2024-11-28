/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:03:57 by anachat           #+#    #+#             */
/*   Updated: 2024/11/27 20:39:55 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			n;
	size_t			i;

	p = NULL;
	n = count * size;
	if (count != 0 && n / count != size)
		return (NULL);
	p = malloc(n);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < n)
		p[i++] = 0;
	return ((void *)p);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	if (size == 0)
		return (len);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}


 
// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	size_t	i;
// 	size_t	j;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1 && s2)
// 		return (strdup(s2));
// 	if (!s2 && s1)
// 		return (strdup(s1));
// 	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[i])
// 		str[j++] = s1[i++];
// 	i = 0;
// 	while (s2[i])
// 		str[j++] = s2[i++];
// 	str[j] = '\0';
// 	return (str);
// }


char    *ft_strjoin(char const *s1, char const *s2)
{
    char    *str;
    size_t    lenght;
    size_t    i;
    size_t    j;

    if (s1 == NULL &&   s2 == NULL)
        return (NULL);
    if (s1 == NULL)
        lenght = ft_strlen(s2);
    else if (s2 == NULL)
        lenght = ft_strlen(s1);
    else 
        lenght = (ft_strlen(s1) + ft_strlen(s2));
    str = (char *)malloc((lenght + 1) * sizeof(char));
    if (str == NULL)
        return (NULL);
    i = 0;
    while (s1 != NULL && i < ft_strlen(s1))
    {
        str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2 != NULL && i < lenght)
        str[i++] = s2[j++];
    str[i] = '\0';
    return (str);
} 