/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:01:55 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:44:28 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	node_len;

	node_len = 0;
	if (lst == NULL)
		return (0);
	while (lst->next)
	{
		node_len++;
		lst = lst->next;
	}
	return (node_len + 1);
}
