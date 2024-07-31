/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:08:42 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/07/21 22:51:08 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_elem)
{
	t_list	*last_node;

	if (*lst == NULL)
	{
		*lst = new_elem;
		return ;
	}
	if (lst && new_elem)
	{
		last_node = ft_lstlast(*lst);
		last_node->next = new_elem;
	}
}
