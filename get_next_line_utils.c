/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    get_next_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:40:51 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/16 13:29:55 by mzhitnik         ###   ########.fr       */
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

unsigned int	ft_copy(char *dest, char const *src, unsigned int start)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[start++] = src[i];
		i++;
	}
	return (start);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	len_s1;
	unsigned int	len_s2;
	char		*str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = 0;
	len_s2 = 0;
	while (s1++)
		len_s1++;
	while (s2++)
		len_s2++;
	str = (char *)malloc(sizeof(char) * ((len_s1 + len_s2) + 1));
	if (!str)
		return (NULL);
	start = 0;
	end = ft_copy(str, s1, start);
	start = end;
	end = ft_copy(str, s2, start);
	str[end] = '\0';
	return (str);
}

void	*ft_calloc(size_t num, size_t size)
{
	size_t	byte_size;
	void	*object;

	byte_size = num * size;
	object = malloc(byte_size);
	if (!object)
		return (NULL);
	while (byte_size--)
		*object++ = 0;
	return (object);
}

char *append_buffer(char *big_buffer, char *buff)
{
 char *temp;

 temp = ft_strjoin(big_buffer, buff);
 free(big_buffer);
 return (temp);
}

char *read_from_file(char *big_buffer, int fd)
{
	char *buff;
	int  bytes_read;

	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
 	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff)
			return (NULL);
		}
		buff[bytes_read] = '\0';
		big_buffer = append_buffer(big_buffer, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free (buff);
	return (big_buffer);
}

