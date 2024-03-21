/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:28:25 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/04 12:16:33 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	j;

	if (little[0] == '\0' || (len == 0 && !big))
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && (size_t)i < len)
	{
		j = 0;
		while (little[j] != '\0' && (size_t)i + j < len)
		{
			if (big[i + j] == little[j])
			{
				j++;
			}
			else
				break ;
		}
		if (little[j] == '\0')
		{
			return ((char *)big + i);
		}
		i++;
	}
	return (0);
}
