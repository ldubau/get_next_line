/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leondubau <leondubau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:41:43 by ldubau            #+#    #+#             */
/*   Updated: 2025/11/23 11:37:27 by leondubau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
# endif

size_t	len_stock(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i ++;
	return (i);
}
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
	str = malloc(sizeof(char) * (len_stock(s1) + len_stock(s2)) + 1);
	if (!str)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		str[i] = s1[i];
		i ++;
	}
	while (s2[j] && s2[j] != '\n')
	{
		str[i + j] = s2[j];
		j ++;
	}
	str[i + j] = '\n';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = (char) c;
	if(!s)
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


char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	char	*line;
	char		*tmp;
	int			size_read;
	int			x;

	x = 0;
	size_read = 1;
	line = ft_strdup("");
	if (!line)
		return (NULL);
	if (buf[0] != '\0')
	{
		line = ft_strdup(ft_strchr(buf, '\n') + 1);
		x = 1;
	}
	while (size_read > 0 && (!ft_strchr(buf, '\n') || x == 1))
	{
		x = 0;
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read < BUFFER_SIZE)
			buf[size_read] = '\0';
		tmp = my_strjoin(line, buf);
		free(line);
		if (!tmp)
			return (NULL);
		line = tmp;
	}
	return (line);
}

int    main(void)
{
    char    *line;
    int        i;
    int        fd;
    fd = open("text.txt", O_RDONLY);
    i = 1;
    while (i < 19)
    {
        line = get_next_line(fd);
        printf("line [%02d]: %s", i, line);
        free(line);
        i++;
    }
	if (i == -1)
	{
		printf("<ERROR>\n");
		close(fd);
		return (-1);
	}
    close(fd);
    return (0);
}

// int main(void)
// {
// 	int fd;
// 	fd = open("text.txt", O_RDONLY);
// 	if (fd != -1)
// 		printf("%s", get_next_line(fd));
// 		printf("%s", get_next_line(fd));
// 		// printf("%s", get_next_line(fd));
// 	return 0;
// }
