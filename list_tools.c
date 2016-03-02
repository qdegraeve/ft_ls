/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:18:26 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/02 23:57:45 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*ft_lst_insert(t_list *lst, void const *content, size_t cont_size)
{
	t_list	*new;

	if (!(new = ft_lstnew(content, cont_size)))
		return (NULL);
	if (!lst)
		lst = new;
	else
	{
		new->next = lst->next;
		lst->next = new;
	}
	return (lst);
}

void	sort_list(t_list **dir)
{
	t_list	*tmp;
	t_list	*swap;
	t_list	*swap2;
	char	*caca;

	tmp = *dir;
	while (tmp)
	{
		caca = tmp->content;
		swap = tmp;
		swap2 = tmp->next;
		while (swap2)
		{
			if (ft_strcmp(caca, swap2->content) > 0)
			{
				swap = swap2;
				caca = swap->content;
			}
			swap2 = swap2->next;
		}
		swap->content = tmp->content;
		tmp->content = caca;
		tmp = tmp->next;
	}
}
