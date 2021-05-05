/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:24:02 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:14:48 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - str : String, to_find : Search String, len : size.
** return - Locations Found Pointer.
** function - Returns the location of a string when it is found.
*/

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (*to_find == 0)
		return ((char *)str);
	while (i < len && str[i])
	{
		j = 0;
		while (i + j < len && str[i + j] && str[i + j] == to_find[j])
			j++;
		if (!to_find[j])
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
