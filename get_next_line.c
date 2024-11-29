/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:38:39 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/29 19:41:04 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" // add this: -D BUFFER_SIZE=(your number)
#include <stdio.h> // DELETE ME

char	*get_next_line(int fd)
{
	static char	*big_buffer;
	char		*line;
	int			line_len;
	int			buff_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!big_buffer)
		big_buffer = ft_calloc(1, sizeof (char));
	if (!big_buffer)
		return (NULL);
	if (!ft_strchr(big_buffer, '\n'))
		read_from_file(&big_buffer, fd);
	if (!big_buffer || !big_buffer[0])
	{
		free(big_buffer);
		return (NULL);
	}
	line_len = 0;
	buff_len = 0;
	while (big_buffer[line_len] && big_buffer[line_len] != '\n')
		line_len++;
	while (big_buffer[buff_len] != '\0')
		buff_len++;
	line = NULL;
	ft_line_res(&big_buffer, &line, buff_len, line_len); // I can save one line wuth return
	return (line);
}
/*//////// MAIN //////////////////////////////////////
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h" 

int	main(int argc, char** argv)
{
	int		fd;
	char	*line;
	int		count;

	(void)argc;
	(void)argv;
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
			{
				printf("Line is NULL");
				break ;
			}
		count++;
		printf("[%d]: %s", count, line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}*/
