/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubau <ldubau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:41:43 by ldubau            #+#    #+#             */
/*   Updated: 2025/11/20 19:58:53 by ldubau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
# endif

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i ++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * ft_strlen(s1) + 1);
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

char	*my_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
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

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = (char) c;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i ++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

void	write_line(char *dst, char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i] = '\0';
}

size_t	len_stock(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i ++;
	return (i);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	static char	*stock;
	char		*line;
	char		*tmp;
	int			size_read;

	size_read = 1;
	stock = ft_strdup("");
	if (!stock)
		return (NULL);
	while (size_read > 0 && !ft_strchr(buf, '\n'))
	{
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read < BUFFER_SIZE)
			buf[size_read] = '\0';
		tmp = my_strjoin(stock, buf);
		free(stock);
		if (!tmp)
			return (NULL);
		stock = tmp;
	}
	line = malloc(sizeof(char) * len_stock(stock) + 1);
	if (!line)
		return (NULL);
	write_line(line, stock);
	return (line);
}



int main(void)
{
	int fd;
	fd = open("text.txt", O_RDONLY);
	if (fd != -1)
		printf("%s", get_next_line(fd));
	return 0;
}
