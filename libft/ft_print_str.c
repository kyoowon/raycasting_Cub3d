/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 00:26:18 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/17 18:56:20 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_print_char(int c, t_option *tp)
{
	int		ret;
	char	set;

	ret = 0;
	if (tp->left == 1)
	{
		tp->zero = 0;
		ret += ft_putchar(c);
	}
	else if (tp->left == 0)
		tp->width--;
	set = ft_issetzero(tp);
	while (ret < tp->width)
	{
		ft_putchar(set);
		ret++;
	}
	if (tp->left == 0)
		ret += ft_putchar(c);
	return (ret);
}

char		*ft_str_prec(char **result, char *str, t_option *tp)
{
	int		i;
	int		len;

	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (tp->prec < len && tp->prec >= 0)
		len = tp->prec;
	if (!(*result = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	(*result)[len] = '\0';
	i = 0;
	while (i < len)
	{
		(*result)[i] = str[i];
		i++;
	}
	return (*result);
}

int			ft_print_str(char *str, t_option *tp)
{
	char	*result;
	int		len;

	result = ft_str_prec(&result, str, tp);
	result = ft_put_width_str(&result, tp, (int)ft_strlen(result));
	len = ft_putstr(result);
	free(result);
	return (len);
}

char		*ft_put_width_str(char **str, t_option *tp, int str_len)
{
	char	*width;
	char	set;
	int		i;

	i = 0;
	if (tp->width > str_len)
	{
		if (!(width = (char *)malloc(sizeof(char) * (tp->width - str_len + 1))))
			return (NULL);
		set = ft_issetzero(tp);
		while (i < (tp->width - str_len))
		{
			width[i] = set;
			i++;
		}
		width[i] = '\0';
		if (tp->left == 0)
			*str = ft_strjoin_two(width, *str);
		else
			*str = ft_strjoin_two(*str, width);
	}
	return (*str);
}
