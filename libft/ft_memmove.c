/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:57:44 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:02:57 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - dest : String to save, src : String to copy, num : size.
** return - Start position of dest.
** function - Copy size from src to dest by size.
** memcpy vs memmove - Processing status for overlap part.
** (memmove : ok memcpy : ko).
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	char		*tmp;
	const char	*sptr;

	if (!dest && !src)
		return (NULL);
	if (dest <= src)
	{
		tmp = dest;
		sptr = src;
		while (num--)
			*tmp++ = *sptr++;
	}
	else
	{
		tmp = dest;
		tmp += num;
		sptr = src;
		sptr += num;
		while (num--)
			*--tmp = *--sptr;
	}
	return (dest);
}
