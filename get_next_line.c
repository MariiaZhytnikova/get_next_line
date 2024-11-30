/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:38:39 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/30 15:45:15 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*big_buffer;
	char		*line;
	size_t		line_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!big_buffer)
		big_buffer = ft_calloc(1, sizeof (char));
	if (!big_buffer)
		return (NULL);
	if (!ft_strchr(big_buffer, '\n'))
		read_from_file(&big_buffer, fd);
	if (!big_buffer || !*big_buffer)
	{
		free(big_buffer);
		big_buffer = NULL;
		return (NULL);
	}
	line_len = 0;
	while (big_buffer[line_len] && big_buffer[line_len] != '\n')
		line_len++;
	line = NULL;
	ft_line_res(&big_buffer, &line, line_len);
	return (line);
}
