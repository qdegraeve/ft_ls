/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:18:26 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/08 19:26:05 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_ascii(t_dircont *c1, void *c2, t_options *o)
{
	if (o->r)
		return (ft_strcmp(((t_dircont*)c2)->name, c1->name));
	else
		return (ft_strcmp(c1->name, ((t_dircont*)c2)->name));
}

int		sort_mod_time(t_dircont *c1, void *c2, t_options *o)
{
	if (o->r)
		return (c1->stat.st_mtime - ((t_dircont*)c2)->stat.st_mtime);
	else
		return (((t_dircont*)c2)->stat.st_mtime - c1->stat.st_mtime);
}

int		sort_access_time(t_dircont *c1, void *c2, t_options *o)
{
	if (o->r)
		return (c1->stat.st_atime - ((t_dircont*)c2)->stat.st_atime);
	else
		return (((t_dircont*)c2)->stat.st_atime - c1->stat.st_atime);
}

void	sort_list(t_list **dir, t_options *o, int (*sort)(t_dircont *, void *,
			t_options *))
{
	t_list		*tmp;
	t_list		*swap2;
	t_dircont	*dc;

	tmp = *dir;
	while (tmp)
	{
		dc = tmp->content;
		swap2 = tmp->next;
		while (swap2 && sort(dc, swap2->content, o) > 0)
		{
			tmp->content = swap2->content;
			tmp->next->content = dc;
			return (sort_list(dir, o, sort));
		}
		tmp = tmp->next;
	}
}

void	sort_select(t_list **dir, t_options *o)
{
	sort_list(dir, o, sort_ascii);
	if (o->t)
		!o->u ? sort_list(dir, o, sort_mod_time) :
			sort_list(dir, o, sort_access_time);
}
