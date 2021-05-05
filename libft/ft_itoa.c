/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 19:23:01 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:01:42 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - nbr : int.
** return - string.(When int_MAX, return to INT_MAX).
** function - Change the number to a string.
** exception - Memory allocation failure, INT_MIN.
*/

#include "libft.h"

static size_t	ft_nbr_len(int nbr)
{
	size_t	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		len = 1;
	while (nbr)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int nbr)
{
	size_t	len;
	size_t	i;
	char	*ret;

	i = 0;
	len = 0;
	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_nbr_len(nbr);
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[len] = '\0';
	if (nbr < 0)
	{
		nbr *= -1;
		ret[i++] = '-';
	}
	while (i < len--)
	{
		ret[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (ret);
}
