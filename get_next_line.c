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

static char *read_from_file(int fd)
{
	int  bytes_read;
	char *buffer;
	static int	count;
		count = 1;
	buffer = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free (buffer);
		return (NULL);
	}
	return (buffer);
}



////////////////////////////////

char *get_next_line(int fd)
{
	char	*bytes_read;

	bytes_read = read_from_file(fd);
	return (bytes_read);
}



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