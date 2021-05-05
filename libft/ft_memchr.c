/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:00:37 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:02:41 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - str : string c :char num : size.
** return - if find char(C) then Return the current(dest) to the next location.
*/

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (*(unsigned char*)(str + i) == (unsigned char)c)
			return ((void*)(str + i));
		i++;
	}
	return (NULL);
}
