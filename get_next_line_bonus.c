/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leondubau <leondubau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:41:43 by ldubau            #+#    #+#             */
/*   Updated: 2025/12/04 13:36:22 by leondubau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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
	free(buf);
	if (size_read < 0)
	{
		free(stock);
		return (NULL);
	}
	return (stock);
}

char	*next_line(char *stock)
{
	char	*tmp;
	if (my_strchr(stock, '\n'))
	{
		tmp = my_strdupe(my_strchr(stock, '\n') + 1);
		free(stock);
		if (!tmp)
			return (NULL);
		stock = tmp;
	}
	else
	{
		free(stock);
		stock = NULL;
	}
	return (stock);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock = NULL;
	int		size_read;

	size_read = 1;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	stock = write_stock(stock, fd, size_read);
	if (!stock)
		return (NULL);
	if (stock[0] == '\0')
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
	line = write_line(stock);
	stock = next_line(stock);
	return (line);
}

//  #include <stdio.h>

// int	main(void)
// {
// 	char	*line;
// 	char	*line2;

// 	int		fd;
// 	int		fd2;
// 	fd = open("text.txt", O_RDONLY);
// 	fd2 = open("text.txt2", O_RDONLY);
// 	line = get_next_line(fd);
// 	line2 = get_next_line(fd2);
// 	while(line && line2)
// 	{
// 		if (line)
// 		{
// 			printf("%s", line);
// 			free(line);
// 			line = get_next_line(fd);
// 		}
// 		if (line2)
// 		{
// 			printf("%s", line2);
// 			free(line2);
// 			line2 = get_next_line(fd2);
// 		}
// 	}
// 	return (0);
// }
