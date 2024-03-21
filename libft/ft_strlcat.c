/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:25:44 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/04 11:37:19 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	a;
	size_t	b;
	size_t	result;

	a = 0;
	b = 0;
	result = 0;
	while (dest[a] != '\0')
		a++;
	while (src[result] != '\0')
		result++;
	if (size <= a)
		result += size;
	else
		result += a;
	while (src[b] != '\0' && (a + 1) < size)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	dest[a] = '\0';
	return (result);
}
