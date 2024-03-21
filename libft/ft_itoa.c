/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:50:56 by nmontiel          #+#    #+#             */
/*   Updated: 2023/04/24 20:04:08 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_dcount(long int n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	n_copy;
	int			n_len;

	n_copy = n;
	if (n_copy < 0)
		n_copy *= -1;
	n_len = ft_dcount(n_copy);
	if (n < 0)
		n_len++;
	str = malloc (sizeof(char) * (n_len + 1));
	if (!str)
		return (NULL);
	str[n_len--] = '\0';
	while (n_len >= 0)
	{
		str[n_len--] = (n_copy % 10) + '0';
		n_copy /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
