/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:16:34 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/04 11:40:56 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*act;

	if (!lst || !del)
		return ;
	while ((*lst))
	{
		del((*lst)->content);
		act = *lst;
		*lst = act->next;
		free(act);
	}
	*lst = 0;
}
