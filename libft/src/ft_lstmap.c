/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:58:44 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/28 10:44:56 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*anew_lst;

	anew_lst = NULL;
	while (lst != NULL)
	{
		new_lst = ft_lstnew((*f)(lst->content));
		if (new_lst == NULL)
		{
			ft_lstclear(&anew_lst, del);
			break ;
		}
		ft_lstadd_back(&anew_lst, new_lst);
		lst = lst->next;
	}
	return (anew_lst);
}
