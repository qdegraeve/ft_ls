/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_n_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:21:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/08 20:53:07 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dir(t_list *sort, t_list *lst, t_display *d)
{
	t_list		*tmp;
	t_dircont	*dc;

	tmp = NULL;
	d->o->l_feed++ ? ft_printf("\n") : 0;
	d->o->name++ ? ft_printf("%s:\n", lst->content) : 0;
	d->o->l ? ft_printf("total %d\n", d->total) : 0;
	while (sort)
	{
		dc = sort->content;
		if (d->o->l)
			display_long(dc, d);
		else
			ft_printf("%s\n", dc->name);
		if (d->o->rec && dc->type[0] == 'd' && ft_isnavdir(dc->name) == 0)
			!d->o->a && ft_ishidden(dc->name) ? 0 :
				ft_lstadd_back(&tmp, dc->path, ft_strlen(dc->path) + 1);
		lst_delone(&sort, del_dircont);
	}
	tmp ? ft_lst_insert(&lst, tmp) : 0;
}

void	set_display(t_display *d, t_stat stat, int namlen, char type)
{
	if (d->len_max < namlen)
		d->len_max = namlen;
	if (d->link_max < ft_num_len(stat.st_nlink))
		d->link_max = ft_num_len(stat.st_nlink);
	if (d->owner_max < (int)ft_strlen((getpwuid(stat.st_uid))->pw_name))
		d->owner_max = ft_strlen((getpwuid(stat.st_uid))->pw_name);
	if (d->group_max < (int)ft_strlen((getgrgid(stat.st_gid))->gr_name))
		d->group_max = ft_strlen((getgrgid(stat.st_gid))->gr_name);
	if (d->size_max < ft_num_len(stat.st_size))
		d->size_max = ft_num_len(stat.st_size);
	if (type == 'b' || type == 'c')
		d->sys = 1;
}

void	stockdir(char *path, DIR *dir, t_list *lst, t_display d)
{
	t_dirent	*fich;
	t_list		*sort;
	t_dircont	dc;

	sort = NULL;
	ft_bzero(&dc, sizeof(dc));
	init_display(&d);
	while ((fich = readdir(dir)))
	{
		dc.path = ft_strcmp(path, "/") ? ft_strjoin(path, "/") :
			ft_strdup(path);
		dc.path = ft_cjoin(dc.path, ft_strdup(fich->d_name));
		lstat(dc.path, &dc.stat);
		dc.name = ft_strdup(fich->d_name);
		dc.type = define_type(dc.stat.st_mode);
		!d.o->a && ((char*)fich->d_name)[0] == '.' ? 0 :
			set_display(&d, dc.stat, fich->d_namlen, dc.type[0]);
		d.total += !d.o->a && ((char*)fich->d_name)[0] == '.' ? 0 :
			dc.stat.st_blocks;
		!d.o->a && ((char*)fich->d_name)[0] == '.' ? 0 :
			ft_lstadd_back(&sort, &dc, sizeof(dc));
	}
	sort_select(&sort, d.o);
	print_dir(sort, lst, &d);
}

void	open_dir(char *av, t_list *lst, t_display d)
{
	DIR		*dir;

	dir = opendir(av);
	if (dir == NULL)
	{
		ft_printf("ls: %s: ", av);
		perror("");
		return ;
	}
	stockdir(av, dir, lst, d);
	if (closedir(dir) == -1)
	{
		ft_printf("%s\n", errno);
		return ;
	}
}
