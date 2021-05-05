/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:12:18 by kyulee            #+#    #+#             */
/*   Updated: 2021/01/07 16:56:51 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** factor - str : String.
** return - size of string.
** function - Measure the length of a string.
*/

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

/*
** factor - str : String to copy.
** return - Start position of result.
** function - Allocate memory space and copy value.
*/

char	*ft_strdup(const char *str)
{
	int		i;
	char	*ret;

	i = 0;
	if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

/*
** factor - str : string, s2 : string.
** return - Start position of result(joined string).
** function - Combine two strings into one string.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(ret = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

/*
** factor - str : string c :char.
** return - if find char(C) then Return the current(str) to the location.
*/

char	*ft_strchr(const char *str, int c)
{
	while (*str != (char)c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char *)str);
}
