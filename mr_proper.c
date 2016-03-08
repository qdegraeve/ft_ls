/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_proper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 18:05:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/08 21:13:48 by qdegraev         ###   ########.fr       */
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

void	del_dircont(void **to_del)
{
	t_dircont	*dc;

	dc = *to_del;
	dc->name ? ft_strdel(&(dc->name)) : 0;
	dc->type ? ft_strdel(&(dc->type)) : 0;
	dc->path ? ft_strdel(&(dc->path)) : 0;
	free (*to_del);
}

void	del_string(void **to_del)
{
	char	*tmp;

	tmp = *to_del;
	ft_strdel(&tmp);
}

void	lst_delone(t_list **lst, void (*del)(void **))
{
	t_list		*tmp;

	tmp = NULL;
	if ((*lst)->prev)
	{
		tmp = (*lst)->prev;
		tmp->next = (*lst)->next;
	}
	tmp = (*lst)->next;
	del(&((*lst)->content));
	ft_bzero(*lst, sizeof(lst));
	*lst = tmp;
}
