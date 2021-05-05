/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:58:10 by kyulee            #+#    #+#             */
/*   Updated: 2020/11/02 17:31:37 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** factor - c : char, set : string.
** return - 0 / 1.
** function - set check.
*/

#include "libft.h"

static size_t	ft_is_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
** factor - s1 : string, set : string.
** return - string (copied string).
** function - Generates a string that has been erased back and forth.
*/

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	len;
	size_t	start;
	size_t	i;

	start = 0;
	len = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_is_set(s1[start], set))
		start++;
	len = ft_strlen(s1);
	while (len > start && ft_is_set(s1[len - 1], set))
		len--;
	if (!(ret = (char *)malloc(sizeof(char) * (len - start + 1))))
		return (NULL);
	while (start < len)
		ret[i++] = s1[start++];
	ret[i] = '\0';
	return (ret);
}
