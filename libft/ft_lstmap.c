/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:19:40 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:44:24 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static t_list	*lst_clear(t_list *lst, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*tmp_node;

	if (!lst || !f)
		return (NULL);
	new_lst = ft_lstnew(f(lst->content));
	if (!new_lst)
		return (lst_clear(lst, del));
	lst = lst->next;
	while (lst)
	{
		tmp_node = ft_lstnew(f(lst->content));
		if (!tmp_node)
			return (lst_clear(lst, del));
		ft_lstadd_back(&new_lst, tmp_node);
		lst = lst->next;
	}
	return (new_lst);
}

static t_list	*lst_clear(t_list *lst, void (*del)(void *))
{
	ft_lstclear(&lst, del);
	return (NULL);
}
