/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:22:57 by nmontiel          #+#    #+#             */
/*   Updated: 2023/10/30 11:47:01 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *x)
{
	size_t	c;

	if (!x)
		exit(EXIT_FAILURE);
	c = 0;
	while (x[c] != '\0')
		c++;
	return (c);
}
