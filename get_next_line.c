/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:38:39 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/27 15:10:57 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" // add this option to your compiler call: -D BUFFER_SIZE=(your number)
#include <unistd.h>        // valgrind, gdb and vgdb
#include <stdio.h> // DELETE MEEEEEE

void	read_from_file(char **big_buffer, int fd)
{
	char *buff;
	char *temp;
	int  bytes_read;

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

void	ft_line_res(char **big_buffer, char **line, int buff_len, int line_len) // get lenghts here
{
	char	*next;
	int		j;

	*line = ft_calloc(line_len + 2, sizeof(char));
	if (!(*line))
		return ;
	j = 0;
	while (**big_buffer && **big_buffer != '\n')
    	(*line)[j++] = *(*big_buffer)++;
	if (*big_buffer == '\n')
		(*line)[j++] = '\n'; 
	(*line)[j] = '\0';
	if (**big_buffer == '\0')
	{
		free(*big_buffer);
		return ;
	}
	next = ft_calloc((buff_len - line_len + 1), sizeof(char));
	if (!next)
		return ;
	j = 0;
	while (**big_buffer != '\0')
		next[j++] = *(*big_buffer)++;
	next[j] = '\0';
	free(*big_buffer);
	*big_buffer = next;
}

char *get_next_line(int fd)
{
	static char	*big_buffer;
	char		*line;
	int		line_len = 0;
	int		buff_len = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!big_buffer)
		big_buffer = ft_calloc(1, sizeof (char));
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
	while (big_buffer[buff_len])
		buff_len++;
	line = NULL;
	ft_line_res(&big_buffer, &line, buff_len, line_len); // lenghts added
	return (line);
}


//////// MAIN //////////////////////////////////////
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h" 

int main(int argc, char** argv)
{
 int  fd;
 char *line;
 int  count;

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
		break ;
	count++;
	printf("[%d]:%s", count, line);
	free(line);
	line = NULL;
 }
 close(fd);
 return (0);
}
