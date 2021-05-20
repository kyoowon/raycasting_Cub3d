/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:30:50 by kyulee            #+#    #+#             */
/*   Updated: 2021/05/19 23:51:47 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - str : String.
** return - size of string.
** function - Measure the length of a string.
*/

#include "libft.h"

int		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}
