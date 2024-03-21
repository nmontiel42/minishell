/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:41:50 by nmontiel          #+#    #+#             */
/*   Updated: 2023/10/30 11:26:55 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	initial_pos(char const *s1, char const *set)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (s1[a])
	{
		while (set[b])
		{
			if (s1[a] == set[b])
			{
				a++;
				break ;
			}
			b++;
		}
		if (b == ft_strlen(set))
			return (a);
		b = 0;
	}
	return (0);
}

static int	final_pos(char const *s1, char const *set)
{
	int		len;
	size_t	j;

	len = 0;
	j = 0;
	while (s1[len])
		len++;
	while (len > 0)
	{
		while (set[j])
		{
			if (s1[len - 1] == set[j])
			{
				len--;
				break ;
			}
			j++;
		}
		if (j == ft_strlen((char *)set))
			return (len);
		j = 0;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		ini;
	int		fin;
	int		i;
	char	*rep_str;

	i = 0;
	ini = initial_pos(s1, set);
	fin = final_pos(s1, set);
	rep_str = malloc(sizeof(char) * (fin - ini + 1));
	if (rep_str == NULL)
		return (NULL);
	while (ini < fin)
	{
		rep_str[i] = s1[ini];
		i++;
		ini++;
	}
	rep_str[i] = '\0';
	return (rep_str);
}
