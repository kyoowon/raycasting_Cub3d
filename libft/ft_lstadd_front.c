/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:30:51 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:27:05 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - lst : Pointing to starting position of the lists, new : new list.
** return - void.
** function - Insert a list at the front of the link list.
*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list *begin;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	begin = new;
	begin->next = *lst;
	*lst = begin;
}
