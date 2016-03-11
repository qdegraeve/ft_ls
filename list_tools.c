/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:18:26 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/11 16:26:31 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_ascii(t_dircont *c1, void *c2, int o)
{
	if (o)
	{
		return (ft_strcmp(((t_dircont*)c2)->name, c1->name));
	}
	else
	{
		return (ft_strcmp(c1->name, ((t_dircont*)c2)->name));
	}
}

int sort_mod_time(t_dircont *c1, void *c2, int o)
{
	long int	l1;
	long int	l2;
	int			diff;

	l1 = (c1->stat.st_mtimespec).tv_nsec;
	l2 = (((t_dircont*)c2)->stat.st_mtimespec).tv_nsec;
	if (o)
	{
		if ((diff = c1->stat.st_mtime - ((t_dircont*)c2)->stat.st_mtime) == 0)
			return (l1 != l2 ? (l1 - l2) : sort_ascii(c1, c2, o));
		else
			return (diff);
	}
	else
	{
		if ((diff = ((t_dircont*)c2)->stat.st_mtime - c1->stat.st_mtime) == 0)
			return (l1 != l2 ? (l2 - l1) : sort_ascii(c1, c2, o));
		else
			return (diff);
	}
}

int		sort_access_time(t_dircont *c1, void *c2, int o)
{
	long int	l1;
	long int	l2;
	int			diff;

	l1 = (c1->stat.st_atimespec).tv_nsec;
	l2 = (((t_dircont*)c2)->stat.st_atimespec).tv_nsec;
	if (o)
	{
		if ((diff = c1->stat.st_atime - ((t_dircont*)c2)->stat.st_atime) == 0)
				return (l1 != l2 ? (l1 - l2) : sort_ascii(c1, c2, o));
			else
				return (diff);
		}
		else
		{
			if ((diff = ((t_dircont*)c2)->stat.st_atime - c1->stat.st_atime) == 0)
				return (l1 != l2 ? (l2 - l1) : sort_ascii(c1, c2, o));
			else
				return (diff);
		}
	}

void	sort_list(t_list **dir, int o, int (*sort)(t_dircont *,
			void *, int))
{
	t_list		*tmp;
	t_list		*swap2;
	t_dircont	*dc;

	tmp = *dir;
	swap2 = NULL;
	if (!tmp || !tmp->next)
		return ;
	swap2 = tmp->next;
	while (swap2)
	{
		dc = tmp->content;
		if (sort(dc, swap2->content, o) > 0)
		{
			tmp->content = swap2->content;
			swap2->content = dc;
			tmp = *dir;
			swap2 = tmp->next;
		}
		else
		{
			tmp = tmp->next;
			swap2 = tmp->next;
		}
	}
}

void	sort_select(t_list **dir, void *content, size_t cont_size, t_options *o)
{
	t_list	*new;

	new = NULL;
	if (!(new = ft_lstnew(content, cont_size)))
		return ;
	if (!(*dir))
		*dir = new;
	else
	{
		if (!o->t)
		{
			ft_lst_sortinsert(dir, new, o->r, sort_ascii);
		}
		else
			!o->u ? ft_lst_sortinsert(dir, new, o->r, sort_mod_time) :
				ft_lst_sortinsert(dir, new, o->r, sort_access_time);
	}
}
