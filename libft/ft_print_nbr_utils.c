/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:16:15 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/17 18:56:10 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trans_baseset(t_option *tp)
{
	if (tp->type == 'd' || tp->type == 'i' || tp->type == 'u')
		return ("0123456789");
	else if (tp->type == 'p' || tp->type == 'x')
		return ("0123456789abcdef");
	else if (tp->type == 'X')
		return ("0123456789ABCDEF");
	else if (tp->type == 'o')
		return ("01234567");
	return (NULL);
}

void	ft_front_sign(char **result, t_option *tp)
{
	if (tp->sign == -1)
	{
		if (tp->zero == 0)
			*result = ft_strjoin_one("-", *result);
		if (tp->zero == 1)
			tp->width--;
	}
	else
	{
		if (tp->zero == 0)
		{
			if (tp->plus == 1)
				*result = ft_strjoin_one("+", *result);
			else if (tp->space == 1)
				*result = ft_strjoin_one(" ", *result);
		}
		if (tp->zero == 1 && (tp->plus || tp->space))
			tp->width--;
	}
}

void	ft_rear_sign(char **result, t_option *tp)
{
	if (tp->zero == 1)
	{
		if (tp->sign == -1)
			*result = ft_strjoin_one("-", *result);
		else if (tp->plus == 1)
			*result = ft_strjoin_one("+", *result);
		else if (tp->space == 1)
			*result = ft_strjoin_one(" ", *result);
	}
}

void	ft_fronthexa_set(char **result, t_option *tp)
{
	if (tp->zero == 0)
	{
		if (tp->type == 'p' || (tp->type == 'x' && tp->hexa == 1))
			*result = ft_strjoin_one("0x", *result);
		else if (tp->type == 'X' && tp->hexa == 1)
			*result = ft_strjoin_one("0X", *result);
		else if (tp->type == 'o' && tp->hexa == 1)
			*result = ft_strjoin_one("0", *result);
	}
	else if (tp->zero == 1 && tp->hexa == 1)
	{
		if (tp->type == 'o')
			tp->width -= 1;
		else
			tp->width -= 2;
	}
}

void	ft_rearhexa_set(char **result, t_option *tp)
{
	if (tp->zero == 1)
	{
		if (tp->type == 'x' && tp->hexa == 1)
			*result = ft_strjoin_one("0x", *result);
		else if (tp->type == 'X' && tp->hexa == 1)
			*result = ft_strjoin_one("0X", *result);
		else if (tp->type == 'o' && tp->hexa == 1)
			*result = ft_strjoin_one("0", *result);
	}
}
