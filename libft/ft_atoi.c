/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 18:08:25 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:01:25 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

static int	check_over_range(unsigned long long sum, int sign)
{
	if (sum > LLONG_MAX - 1 && sign == -1)
		return (0);
	if (sum > LLONG_MAX && sign == 1)
		return (-1);
	return (sum * sign);
}

/*
** factor - nptr : String to replace with number.
** return - int type nub.
** function - Replace a numeric string with a number.
*/

int			ft_atoi(const char *nptr)
{
	int					i;
	int					sign;
	unsigned long long	nbr;

	i = 0;
	sign = 1;
	if (*nptr == 0)
		return (0);
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	nbr = 0;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
		nbr = (nbr * 10) + nptr[i++] - '0';
	return (check_over_range(nbr, sign));
}
