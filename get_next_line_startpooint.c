/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_to long.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:38:39 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/26 15:33:45 by mzhitnik         ###   ########.fr       */
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

void	ft_line_res(char **big_buffer, char **line)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	while ((*big_buffer)[i] && (*big_buffer)[i] != '\n')
		i++;
	*line = ft_calloc(i + 2, sizeof(char));
	j = 0;
	while (j < i)
	{
		(*line)[j] = (*big_buffer)[j];
		j++;
	}
	if ((*big_buffer)[j] == '\n')
		(*line)[j++] = '\n'; 
	(*line)[j] = '\0';
	////////////////////NEXT//////////////////////////////
	if ((*big_buffer)[i] == '\0')
	{
		free(big_buffer);
		return ;
	}
	next = ft_calloc((ft_strlen(*big_buffer) - i++ + 1), sizeof(char));
	j = 0;
	while ((*big_buffer)[i] != '\0')
		next[j++] = (*big_buffer)[i++];
	next[j] = '\0';
	free(*big_buffer);
	*big_buffer = next;
	////////////////////////////////////////////////////////
}

char *get_next_line(int fd)
{
	static char	*big_buffer;
	char		*line;

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
	line = NULL;
	ft_line_res(&big_buffer, &line);
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
