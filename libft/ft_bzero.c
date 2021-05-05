/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:48:14 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:01:19 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - str : Sting, num : len-size.
** return - void.
** function - Set a value of zero to a string.
*/

#include "libft.h"

void	ft_bzero(void *str, size_t num)
{
	size_t i;

	i = 0;
	while (i < num)
	{
		*((unsigned char *)str + i) = 0;
		i++;
	}
}
