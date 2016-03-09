/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_proper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 18:05:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/09 18:29:39 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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

void	del_dircont(void *to_del)
{
	t_dircont	*dc;

	dc = to_del;
	free(dc->name);
	free(dc->type);
	free(dc->path);
	free(to_del);
}

void	del_string(void *to_del)
{
	char	*tmp;

	tmp = to_del;
	ft_strdel(&tmp);
}

void	lst_delone(t_list **lst, void (*del)(void *))
{
	t_list		*tmp;

	tmp = NULL;
	tmp = (*lst)->next;
	del((*lst)->content);
	free(*lst);
	*lst = tmp;
}
