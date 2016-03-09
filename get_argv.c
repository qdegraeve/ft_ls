/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 16:14:47 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/09 18:27:00 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_params(t_list *tmp, t_list **lst, t_display *d)
{
	t_dircont	*dc;
	int			i;

	i = 0;
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
		lst_delone(&tmp, del_dircont);
	}
}

void	filter_params(t_list *sort, t_list **lst, t_display *d)
{
	t_list		*tmp;
	t_dircont	*dc;
	t_stat		stat;

	tmp = NULL;
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
			set_display(d, dc->stat, ft_strlen(dc->name), dc->type[0]);
			ft_lstadd_back(&tmp, dc, sizeof(*dc));
		}
		sort = sort->next;
	}
	sort_select(&tmp, d->o);
	print_params(tmp, lst, d);
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
		if (lstat(av[i], &dc.stat) != 0 && !av[i][0])
		{
			ft_printf("ls: fts_open: ");
			perror("");
			exit(EXIT_FAILURE);
		}
		dc.name = ft_strdup(av[i]);
		dc.type = define_type(dc.stat.st_mode);
		dc.path = NULL;
		ft_lstadd_back(&sort, &dc, sizeof(dc));
		i++;
	}
	sort_list(&sort, 0, sort_ascii);
	filter_params(sort, lst, &d);
}
