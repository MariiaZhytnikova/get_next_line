/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:40:45 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/28 14:26:23 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
#include <unistd.h> 
#include <stdint.h>

# ifndef	BUFFER_SIZE
# define	BUFFER_SIZE 3
#endif

char	*get_next_line(int fd);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t num, size_t size);
void	read_from_file(char **big_buffer, int fd);
char	*ft_line_res(char **big_buffer, char **line, int buff_len, int line_len);

#endif
