/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:26:51 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/04 12:16:00 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			count;
	unsigned char	*dst;

	count = 0;
	dst = (unsigned char *) b;
	while (count < len)
	{
		dst[count] = (unsigned char) c;
		count++;
	}
	return (b);
}
