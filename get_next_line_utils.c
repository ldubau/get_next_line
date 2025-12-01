/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leondubau <leondubau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:07:47 by leondubau         #+#    #+#             */
/*   Updated: 2025/12/01 13:58:49 by leondubau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	my_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i ++;
	return (i);
}

char	*my_strdupe(const char *s1)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * my_strlen(s1) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i ++;
	}
	str[i] = '\0';
	return (str);
}

char	*my_strjoin(char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * my_strlen(s1) + my_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i ++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j ++;
	}
	str[i + j] = '\0';
	return (str);
}

void	*my_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	if (count * size > (size_t) - 1)
		return (NULL);
	ptr = malloc(count * size);
	i = 0;
	if (!ptr)
		return (NULL);
	while (i < count * size)
	{
		ptr[i] = '\0';
		i ++;
	}
	return (ptr);
}
