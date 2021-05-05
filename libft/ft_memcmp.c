/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:22:23 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:02:45 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - str : string c :char num : size.
** return - if find char(C) then Return the current(dest) to the next location.
** function - Copy from src to dest by size (Return : if c is found).
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t num)
{
	size_t i;

	i = 0;
	while (i < num)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}
