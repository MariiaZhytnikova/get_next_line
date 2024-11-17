/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:40:45 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/16 13:47:57 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# ifndef	BUFFER_SIZE
# define	BUFFER_SIZE 3
#endif

char          *get_next_line(int fd);
char	        *ft_strchr(const char *str, int c);
unsigned int	ft_copy(char *dest, char const *src, unsigned int start);
char	        *ft_strjoin(char const *s1, char const *s2);
void	        *ft_calloc(size_t num, size_t size);
char          *append_buffer(char *big_buffer, char *buff);
char          *read_from_file(char *big_buffer, int fd);

#endif
