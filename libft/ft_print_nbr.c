/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 19:23:01 by kyulee            #+#    #+#             */
/*   Updated: 2021/05/17 18:56:54 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_printf_nbr_len(long long nbr, t_option *tp)
{
	int		len;

	len = 0;
	if (nbr == 0 && tp->prec != 0)
		return (1);
	while (nbr != 0)
	{
		nbr = nbr / tp->baseset;
		len++;
	}
	return (len);
}

int			ft_check_prec(int nbr_len, t_option *tp)
{
	int		len;

	len = 0;
	if (tp->prec > nbr_len)
		len = tp->prec;
	else
		len = nbr_len;
	return (len);
}

char		*ft_nbr_itoa(char **result, unsigned long long nbr, t_option *tp)
{
	int		nbr_len;
	int		len;
	int		i;

	nbr_len = ft_printf_nbr_len(nbr, tp);
	len = ft_check_prec(nbr_len, tp);
	if (!(*result = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	(*result)[len] = '\0';
	i = 0;
	while (i < tp->prec - nbr_len)
		(*result)[i++] = '0';
	i = len;
	while (--i >= 0)
	{
		(*result)[i] = ft_trans_baseset(tp)[nbr % tp->baseset];
		nbr = nbr / tp->baseset;
	}
	return (*result);
}

int			ft_signed_nbr(long long nbr, t_option *tp)
{
	int		len;
	char	*result;

	if (nbr < 0)
	{
		nbr *= -1;
		tp->sign = -1;
	}
	if (tp->left == 1 || tp->prec > -1)
		tp->zero = 0;
	result = ft_nbr_itoa(&result, nbr, tp);
	ft_front_sign(&result, tp);
	result = ft_put_width_str(&result, tp, (int)ft_strlen(result));
	ft_rear_sign(&result, tp);
	len = ft_putstr(result);
	free(result);
	return (len);
}

int			ft_unsigned_nbr(unsigned long long nbr, t_option *tp)
{
	int		len;
	char	*result;

	if (tp->type == 'x' || tp->type == 'X' || tp->type == 'p')
		tp->baseset = 16;
	if (tp->type == 'o')
		tp->baseset = 8;
	if (tp->left == 1 || tp->prec > -1)
		tp->zero = 0;
	result = ft_nbr_itoa(&result, nbr, tp);
	if (tp->type == 'p' || nbr != 0)
		ft_fronthexa_set(&result, tp);
	result = ft_put_width_str(&result, tp, (int)ft_strlen(result));
	if (tp->type == 'p' || nbr != 0)
		ft_rearhexa_set(&result, tp);
	len = ft_putstr(result);
	free(result);
	return (len);
}
