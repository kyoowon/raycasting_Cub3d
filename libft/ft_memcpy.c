/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:19:41 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:02:49 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - dest : String to save, src : String to copy, num : size.
** return - Start position of dest.
** function - Copy size from src to dest by size.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	const void *dstptr;

	dstptr = dest;
	if (!dest && !src)
		return (NULL);
	while (num--)
		*((unsigned char *)dest++) = *((unsigned char *)src++);
	return ((void *)dstptr);
}
