/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlongestsize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 23:46:10 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/25 17:20:59 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstlongestsize(t_list *lst)
{
	int max;

	max = -1;
	while (lst)
	{
		if (max < ft_strlen((char *)lst->content))
			max = ft_strlen((char *)lst->content);
		lst = lst->next;
	}
	return (max);
}
