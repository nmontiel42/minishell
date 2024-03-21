/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:04:25 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/04 12:15:57 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*ptr_dst;
	char		*ptr_src;

	i = 0;
	ptr_dst = (char *)dst;
	ptr_src = (char *)src;
	if (dst == NULL && src == NULL)
		return (0);
	if (ptr_dst > ptr_src)
	{
		while (n-- != 0)
			ptr_dst[n] = ptr_src [n];
	}
	else
	{
		while (i < n)
		{
			ptr_dst[i] = ptr_src[i];
			i++;
		}
	}
	return (dst);
}
