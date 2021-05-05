/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 18:41:25 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:01:22 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - nmenb : bit sizes of type, size : len.
** return - Start position of string.
** function - Set a value of zero to a string.
*/

#include "libft.h"

void	*ft_calloc(size_t nmenb, size_t size)
{
	void *ret;

	if (!(ret = (void*)malloc(nmenb * size)))
		return (NULL);
	ft_bzero(ret, nmenb * size);
	return (ret);
}
