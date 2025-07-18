/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:16:35 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/08 16:16:37 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list_del;

	if (!del)
		return ;
	while (*lst)
	{
		list_del = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = list_del;
	}
}
