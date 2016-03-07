/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:31:35 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/07 17:56:49 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_display(t_display *d)
{
	d->len_max = 0;
	d->link_max = 0;
	d->owner_max = 0;
	d->group_max = 0;
	d->size_max = 0;
	d->total = 0;
}

void	init_options(t_options *o)
{
	o->name = 0;
	o->l_feed = 0;
	o->rec = 0;
	o->l = 0;
	o->a = 0;
	o->r = 0;
	o->t = 0;
}

int		check_options(char **av, t_options *o)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strcmp(av[i], "--") == 0)
			return (i + 1);
		else if (av[i][1] == '\0')
			return (i);
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] == 'R')
				o->rec = 1;
			else if (av[i][j] == 'l')
				o->l = 1;
			else if (av[i][j] == 'a')
				o->a = 1;
			else if (av[i][j] == 'r')
				o->r = 1;
			else if (av[i][j] == 't')
				o->t = 1;
			else if (av[i][j] == '1')
				o->one = 1;
			else
			{
				ft_printf("ls: illegal option -- %c\n", av[i][j]);
				ft_putendl("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1 \
						[file ...]\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (i);
}

void	print_params(t_list *sort, t_list **lst, t_display *d)
{
	t_list		*tmp = NULL;
	t_dircont	*dc;
	t_stat		stat;

	while (sort)
	{
		dc = sort->content;
		if (lstat(dc->name, &stat) != 0)
		{
			ft_printf("ls: %s: ", dc->name);
			perror("");
			d->o->name++;
		}
		else
		{
			set_display(d, dc->stat, ft_strlen(dc->name));
			ft_lstadd_back(&tmp, dc, sizeof(*dc));
		}
		sort = sort->next;
	}
	while (tmp)
	{
		dc = tmp->content;
		if (dc->type[0] == 'd')
			ft_lstadd_back(lst, dc->name, ft_strlen(dc->name) + 1);
		else
		{
			if (d->o->l)
				display_long(dc, d);
			else
				ft_printf("%s\n", dc->name);
			d->o->l_feed++;
		}
		tmp = tmp->next;
	}
}

void	sort_params(char **av, t_list **lst, t_options *o, t_display d)
{
	int			i;
	t_dircont	dc;
	t_list		*sort;

	i = 0;
	init_display(&d);
	d.o = o;
	while (av[i])
	{
		lstat(av[i], &dc.stat);
		dc.name = ft_strdup(av[i]);
		dc.type = define_type(dc.stat.st_mode);
		ft_lstadd_back(&sort, &dc, sizeof(dc));
		i++;
	}
	!d.o->t ? sort_list(&sort, d.o) : sort_list_time(&sort, d.o);
	print_params(sort, lst, &d);
}

int		main(int ac, char **av)
{
	int			i;
	t_options	o;
	t_display	d;
	t_list		*lst;

	lst = NULL;
	init_options(&o);
	if ((i = check_options(av, &o)) == ac)
		ft_lstadd_back(&lst, ".", 2);
	else
	{
		i + 1 < ac ? o.name++ : 0;
		sort_params(av + i, &lst, &o, d);
	}
	d.o = &o;
	while (lst)
	{
		open_dir(lst->content, lst, d);
		lst = lst->next;
	}
	return (0);
}
