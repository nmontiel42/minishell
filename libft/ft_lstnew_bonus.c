/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:40:33 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/04 11:40:38 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*new_l;

	new_l = (t_list *)malloc(sizeof(t_list));
	if (!new_l)
		return (NULL);
	new_l->content = ft_strdup(content);
	if (!new_l->content)
	{
		free(new_l);
		return (NULL);
	}
	new_l->next = NULL;
	return (new_l);
}
