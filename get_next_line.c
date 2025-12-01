/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leondubau <leondubau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:41:43 by ldubau            #+#    #+#             */
/*   Updated: 2025/12/01 14:01:18 by leondubau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*my_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = (char) c;
	if (!s)
		return (NULL);
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

char	*write_line(const char *str)
{
	int		size;
	char	*res;
	int		i;

	i = 0;
	size = 0;
	if (!str)
		return (NULL);
	while (str[size] != '\0' && str[size] != '\n')
		size ++;
	if (str[size] == '\n')
		size ++;
	res = malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	while (i < size)
	{
		res[i] = str[i];
		i ++;
	}
	res[i] = '\0';
	return (res);
}

char	*write_stock(char *stock, int fd, int size_read)
{
	char	*buf;
	char	*tmp;

	buf = my_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (size_read > 0 && !my_strchr(stock, '\n'))
	{
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read <= 0)
			break ;
		buf[size_read] = 0;
		tmp = my_strjoin(stock, buf);
		if (!tmp)
			return (NULL);
		if (stock)
			free(stock);
		stock = tmp;
	}
	return (stock);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock = NULL;
	char		*tmp;
	int		size_read;

	size_read = 1;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	tmp = NULL;
	stock = write_stock(stock, fd, size_read);
	if (!stock)
		return (NULL);
	line = write_line(stock);
	if (my_strchr(stock, '\n'))
	{
		tmp = my_strdupe(my_strchr(stock, '\n') + 1);
		free(stock);
		if (!tmp)
			return (NULL);
		stock = tmp;
	}
	else if (my_strchr(stock, '\0'))
	{
		line = stock;
		// free(stock);
		stock = NULL;
	}
	return (line);
}

 #include <stdio.h>

int	main(void)
{
	char	*line;
	// int		i;
	int		fd;
	fd = open("43_with_nl", O_RDONLY);
	// i = 1;
	line = get_next_line(fd);
	while(line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
