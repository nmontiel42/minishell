/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:57:10 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/04 11:40:54 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list	*act;

	if (!lst || !del)
		return ;
	del(lst->content);
	act = lst;
	lst = act->next;
	free(act);
	lst = 0;
}
