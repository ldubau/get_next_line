/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leondubau <leondubau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:14:09 by leondubau         #+#    #+#             */
/*   Updated: 2025/12/01 11:14:46 by leondubau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 24
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*write_stock(char *stock, int fd, int size_read);
char	*write_line(const char *str);
char	*my_strchr(const char *s, int c);
char	*my_strjoin(char *s1, const char *s2);
char	*my_strdupe(const char *s1);
void	*my_calloc(size_t count, size_t size);
size_t	my_strlen(const char *s);

#endif
