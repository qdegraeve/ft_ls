/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:18:26 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/03 17:56:42 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"



void	ft_lst_insert(t_list **lst, t_list *in)
{
	t_list	*tmp;

	tmp = NULL;
	if (!*lst)
		*lst = in;
	else
	{
		tmp = in;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (*lst)->next;
		(*lst)->next = in;
	}
	tmp = *lst;
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
