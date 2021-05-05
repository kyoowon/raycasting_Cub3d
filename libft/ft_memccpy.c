/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 19:24:37 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:02:36 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - dest : String to save, src : String to copy.
** c : Stop and return when char(c) is found num : copy size.
** return - if find char(C) then Return the current(dest) to the next location
** else return NULL.
** function - Copy from src to dest by size (Return : if c is found).
*/

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t num)
{
	size_t i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < num)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		if (*(unsigned char *)(src + i) == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
