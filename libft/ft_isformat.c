/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isformat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:20:01 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/25 17:21:09 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isformat(char *str, char *format)
{
	int		len_str;
	int		len_fmt;
	char	*fmt_of_str;

	len_str = ft_strlen(str);
	len_fmt = ft_strlen(format);
	if (len_str <= len_fmt)
		return (0);
	fmt_of_str = str + len_str - len_fmt;
	if (ft_strcmp(fmt_of_str, format) == 0)
		return (1);
	return (0);
}
