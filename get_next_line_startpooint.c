/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:38:39 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/22 12:49:33 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" // add this option to your compiler call: -D BUFFER_SIZE=(your number)
#include <unistd.h>        // valgrind, gdb and vgdb
#include <stdio.h> // DELETE MEEEEEE

char	*read_from_file(char *big_buffer, int fd) // Read from file
{
	char *buff;
	char *temp;
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
			free(buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
 		temp = ft_strjoin(big_buffer, buff);
 		free(big_buffer);
 		big_buffer = temp;
		if (ft_strchr(buff, '\n')) // we read from file till find '/n' symbol
			break ;
	}
	free (buff);
	return (big_buffer); // I want to use pointers
}

char	*ft_current_line(char *big_buffer, char *line) // Line for return // I can combine the current line and next
{
	int		i;
	int		j;
	char	*next;

	i = 0;
//	if (!buffer[i])
//		return ;
	while (big_buffer[i] && big_buffer[i] != '\n') // len of our new line
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	j = 0;
	while (big_buffer[j] && big_buffer[j] != '\n') // copy buffer too new line
	{
		line[j] = big_buffer[j];
		j++;
	}
	printf("current line before NULL terminating is: %s\n", line);
	if (big_buffer[j] && big_buffer[j] == '\n')    // '\0' terminate line
		line[j] = '\0';
	printf("current line after is: %s\n", line);
	next = ft_calloc((ft_strlen(big_buffer) - i + 1), sizeof(char)); // allocate memory for begining of next line
	i++;															 // skip \n symbol
	j = 0;
	while (big_buffer[i])
		next[j++] = big_buffer[i++]; 								 // copy from buffer to next line
	free(big_buffer);
	return (next);		
}

char *get_next_line(int fd)
{
	static char	*big_buffer;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)  // Start check
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
	line = NULL;
	big_buffer = ft_current_line(big_buffer, line);
	printf("BIG_BUFF after new line extracted: %s\n", line);
	printf("BIG_BUFF after new line extracted: %s\n", big_buffer);
	return (line);
}


//////// MAIN //////////////////////////////////////
#include <unistd.h>
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
		{
			//printf ("EOF or smthng wrong: line == NULL!");
			break ;
		}
		count++;
		printf("[%d]:%s\n", count, line);
		free(line);
		line = NULL;
		}
	close(fd);
	return (0);
}
