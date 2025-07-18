/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:49:26 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/08 18:49:29 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*aux;
	t_list	*temporal;
	t_list	*new_node;

	aux = NULL;
	while (lst)
	{
		temporal = (t_list *)malloc(sizeof(t_list));
		if (!temporal)
		{
			ft_lstclear(&aux, del);
			return (NULL);
		}
		temporal->content = f(lst->content);
		temporal->next = NULL;
		if (!aux)
			aux = temporal;
		else
			new_node->next = temporal;
		new_node = temporal;
		lst = lst->next;
	}
	return (aux);
}
