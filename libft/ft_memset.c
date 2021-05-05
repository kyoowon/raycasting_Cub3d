/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:23:25 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:03:00 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - str: string, value : value, num : size.
** return - Start position of string.
** function - Set a value to a string.
*/

#include "libft.h"

void	*ft_memset(void *str, int value, size_t num)
{
	while (num--)
		*((unsigned char*)str + num) = (unsigned char)value;
	return (str);
}
