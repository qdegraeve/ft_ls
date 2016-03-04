/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:18:26 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/04 20:20:39 by qdegraev         ###   ########.fr       */
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

void	sort_list(t_list **dir, t_options *o)
{
	t_list		*tmp;
	t_list		*swap;
	t_list		*swap2;
	t_dircont	*caca;

	tmp = *dir;
	while (tmp)
	{
		caca = tmp->content;
		swap = tmp;
		swap2 = tmp->next;
		while (swap2)
		{
			if (!o->r ? ft_strcmp(caca->name, ((t_dircont*)swap2->content)
					->name) > 0 : ft_strcmp(caca->name,
						((t_dircont*)swap2->content)->name) < 0)
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

void	sort_list_time(t_list **dir, t_options *o)
{
	t_list		*tmp;
	t_list		*swap;
	t_list		*swap2;
	t_dircont	*caca;

	tmp = *dir;
	while (tmp)
	{
		caca = tmp->content;
		swap = tmp;
		swap2 = tmp->next;
		while (swap2)
		{
			if (!o->r ? caca->stat.st_mtime < ((t_dircont*)swap2->content)->stat.st_mtime : caca->stat.st_mtime > ((t_dircont*)swap2->content)->stat.st_mtime)
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
