/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    get_next_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:40:51 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/16 13:29:55 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


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

