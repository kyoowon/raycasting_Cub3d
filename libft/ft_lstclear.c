/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:30:24 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:27:09 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - lst : Pointing to starting position of lists, del fuction pointer.
** return - void.
** function - list clear.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *tmp;

	if (!lst || !del)
		return ;
	while (*lst && lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		(*del)(tmp->content);
		free(tmp);
	}
}
