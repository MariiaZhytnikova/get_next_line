/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:38:39 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/30 15:56:06 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*big_buffer[1024];
	char		*line;
	size_t		line_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
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
		big_buffer[fd] = NULL;
		return (NULL);
	}
	line_len = 0;
	while (big_buffer[fd][line_len] && big_buffer[fd][line_len] != '\n')
		line_len++;
	line = NULL;
	ft_line_res(&big_buffer[fd], &line, line_len);
	return (line);
}
