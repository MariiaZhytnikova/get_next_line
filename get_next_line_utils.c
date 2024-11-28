/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:40:51 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/28 18:36:17 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*res;
	size_t	i;

	res = NULL;
	s1_len = 0;
	s2_len = 0;
	if (s1)
		while (s1[s1_len])
			s1_len++;
	if (s2)
		while (s2[s2_len])
			s2_len++;
	res = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < s1_len)
		res[i++] = *s1++;
	while (i < s1_len + s2_len)
		res[i++] = *s2++;
	return (res);
}

void	*ft_calloc(size_t num, size_t size)
{
	size_t			byte_size;
	size_t			i;
	unsigned char	*object;

	if (size != 0 && num > (SIZE_MAX / size))
		return (NULL);
	byte_size = num * size;
	if (byte_size == 0)
		return (NULL);
	object = malloc(byte_size);
	if (!object)
		return (NULL);
	i = 0;
	while (i < byte_size)
	{
		object[i] = 0;
		i++;
	}
	return ((void *)object);
}

void	read_from_file(char **big_buffer, int fd)
{
	char	*buff;
	char	*temp;
	int		bytes_read;

	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return ;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			return ;
		}
		buff[bytes_read] = '\0';
		temp = ft_strjoin(*big_buffer, buff);
		free(*big_buffer);
		*big_buffer = temp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free (buff);
}

void	ft_line_res(char **big_buffer, char **line, int buff_len, int line_len)
{
	char	*next;
	int		j;
	int		i;

	*line = ft_calloc(line_len + 2, sizeof(char));
	if (!(*line))
		return ;
	j = 0;
	while (j++ < line_len)
		(*line)[j - 1] = (*big_buffer)[j - 1];
	j--;
	if ((*big_buffer)[j] == '\n')
		(*line)[j++] = '\n';
	(*line)[j++] = '\0';
	j = 0;
	i = line_len +1;
	next = ft_calloc(buff_len - line_len + 1, sizeof(char));
	if (!next)
		return ;
	while ((*big_buffer)[i] != '\0')
		next[j++] = (*big_buffer)[i++];
	next[j] = '\0';
	free(*big_buffer);
	*big_buffer = next;
}
