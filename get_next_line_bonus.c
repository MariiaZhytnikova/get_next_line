/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:38:39 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/28 18:52:31 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h" // add this: -D BUFFER_SIZE=(your number)

char	*get_next_line(int fd)
{
	static char	*big_buffer[1024];
	char		*line;
	int			line_len;
	int			buff_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!big_buffer[fd])
		big_buffer[fd] = ft_calloc(1, sizeof (char));
			if (!big_buffer[fd])
				return (NULL);
	if (!ft_strchr(big_buffer[fd], '\n'))
		read_from_file(&big_buffer[fd], fd);
	if (!big_buffer[fd] || !*big_buffer[fd])
	{
		free(big_buffer[fd]);
		return (NULL);
	}
	line_len = 0;
	buff_len = 0;
	while (big_buffer[fd][line_len] && big_buffer[fd][line_len++] != '\n')
	while (big_buffer[fd][buff_len++])
	line = NULL;
	big_buffer[fd] = ft_line_res(&big_buffer[fd], &line, buff_len, line_len - 1);
	return (line);
}

//////// MAIN //////////////////////////////////////
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char** argv)
{
	int		fd;
	int		fd2;
	char	*line;
	int		count;
	int		count2;

	(void)argc;
	(void)argv;
	count = 0;
	count2 = 0;
	fd = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
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
		printf("[%d]: %s", count, line);
		free(line);
		line = NULL;
		line = get_next_line(fd2);
		if (line == NULL)
			break ;
		count2++;
		printf("[%d]: %s", count2, line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count++;
		printf("[%d]: %s", count, line);
		free(line);
		line = NULL;
		line = get_next_line(fd2);
		if (line == NULL)
			break ;
		count2++;
		printf("[%d]: %s", count2, line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count++;
		printf("[%d]: %s", count, line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}
