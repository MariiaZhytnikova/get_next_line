/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:38:39 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/16 13:50:48 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" // add this option to your compiler call: -D BUFFER_SIZE=(your number)
# include <unistd.h>

///// UTILS

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (*s != '\0')
	{
		counter++;
		s++;
	}
	return (counter);
}

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

static unsigned int	ft_copy(char *dest, char const *src, unsigned int start)
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
	unsigned int		start;
	unsigned int		end;
	unsigned int		len_s1;
	unsigned int		len_s2;
	char				*str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
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

void	ft_bzero(void *str, size_t n)
{
	char	*p;

	if (str == NULL || n == 0)
		return ;
	p = (char *)str;
	while (n--)
		*p++ = 0;
}

void	*ft_calloc(size_t num, size_t size)
{
	size_t	byte_size;
	void	*object;

	byte_size = num * size;
	object = malloc(byte_size);
	if (!object)
		return (NULL);
	ft_bzero (object, byte_size);
	return (object);
}

char *append_buffer(char *big_buffer, char *buff)
{
 char *temp;

 temp = ft_strjoin(big_buffer, buff);
 free(big_buffer);
 return (temp);
}

static char *read_from_file(char *big_buffer, int fd)
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



////////////////////////////////

char *get_next_line(int fd)
{
	static char	*big_buffer;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0) 
		return (NULL);
	if (!big_buffer)
		big_buffer = ft_calloc(1, sizeof (char)); 
	if (!ft_strchr(big_buffer, '\n'))
		big_buffer = read_from_file(big_buffer, fd);
	if (!big_buffer)
	{
		free(big_buffer);
		return (NULL);
	}
	line = extract_line(big_buffer);
	big_buffer = obtain_remaining(big_buffer);
	return (line);
}


//////// MAIN //////////////////////////////////////
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h" 

int main(void)
{
	int    fd;
	char  *line;
	int  count;

	count = 0;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count++;
		printf("[%d]:%s\n", count, line);
		free(line);
		line = NULL;
		}
	close(fd);
	return (0);
}
