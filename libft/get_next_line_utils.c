/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:37:10 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/23 15:00:18 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gn(char const *s1, char const *s2)
{
	char	*ret_str;
	size_t	len;
	int		i;
	int		a;

	i = 0;
	a = 0;
	len = ((size_t)ft_strlen(s1) + (size_t)ft_strlen(s2));
	ret_str = (char *)malloc(((len + 1) * sizeof(char)));
	if (!ret_str)
		return (NULL);
	while (s1[i])
	{
		ret_str[i] = s1[i];
		i++;
	}
	while (s2[a])
	{
		ret_str[i + a] = s2[a];
		a++;
	}
	ret_str[i + a] = '\0';
	return (ret_str);
}

void	*ft_calloc_gnl(size_t num, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)malloc(size * num);
	if (!ptr)
		return (0);
	i = 0;
	while (i < (num * size))
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

size_t	ft_strlen_gn(const char *str)
{
	int	cont;

	cont = 0;
	while (str[cont] != '\0')
	{
		cont++;
	}
	return (cont);
}

int	ft_strchr_mod(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}
