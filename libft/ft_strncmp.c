/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:34:52 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:10:43 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** factor - c1 : char, c2 : char.
** return - difference value of ASCII.
** function - Compare two chars(if same then return 0).
*/

static int	cmp_char(char c1, char c2)
{
	if ((unsigned char)c1 != (unsigned char)c2)
		return ((unsigned char)c1 - (unsigned char)c2);
	return (0);
}

/*
** factor - s1 : String, s2 : String, num : size.
** return - difference value of ASCII.
** function - Compare two strings.
*/

int			ft_strncmp(const char *s1, const char *s2, size_t num)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < num)
	{
		if (cmp_char(s1[i], s2[i]))
			return (cmp_char(s1[i], s2[i]));
		i++;
	}
	if (i < num)
		return (cmp_char(s1[i], s2[i]));
	return (0);
}
