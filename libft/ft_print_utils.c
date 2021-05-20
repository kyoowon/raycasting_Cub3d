/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 23:58:15 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/17 18:56:42 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int			ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i++], 1);
	}
	return (i);
}

void		ft_init(t_option *tp)
{
	tp->type = 0;
	tp->width = 0;
	tp->prec = -1;
	tp->zero = 0;
	tp->left = 0;
	tp->sign = 1;
	tp->baseset = 10;
	tp->len = 0;
	tp->plus = 0;
	tp->space = 0;
	tp->hexa = 0;
}

char		ft_issetzero(t_option *tp)
{
	if (tp->zero == 1)
		return ('0');
	else
		return (' ');
}
