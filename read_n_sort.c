/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_n_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:21:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/11 15:34:59 by qdegraev         ###   ########.fr       */
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
	!d->o->l || !sort  ? 0 : ft_printf("total %d\n", d->total);
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
	struct group	*gr;
	struct passwd	*pwd;

	pwd = getpwuid(stat.st_uid);
	gr = getgrgid(stat.st_gid);
	if (d->len_max < namlen)
		d->len_max = namlen;
	if (d->link_max < ft_num_len(stat.st_nlink))
		d->link_max = ft_num_len(stat.st_nlink);
	if (pwd && pwd->pw_name && d->owner_max < (int)ft_strlen(pwd->pw_name))
		d->owner_max = ft_strlen(pwd->pw_name);
	else if (!pwd && !pwd->pw_name && d->owner_max < ft_num_len(stat.st_uid))
		d->owner_max = ft_num_len(stat.st_uid);
	if (gr && gr->gr_name && d->group_max < (int)ft_strlen(gr->gr_name))
		d->group_max = ft_strlen(gr->gr_name);
	else if (!gr && !gr->gr_name && d->group_max < ft_num_len(stat.st_gid))
		d->group_max = ft_num_len(stat.st_gid);
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
		if (d.o->a || fich->d_name[0] != '.')
		{
			dc.path = ft_strcmp(path, "/") ? ft_strjoin(path, "/") : 
				ft_strdup(path);
			dc.path = ft_cjoin(dc.path, ft_strdup(fich->d_name));
			lstat(dc.path, &dc.stat);
			dc.name = ft_strdup(fich->d_name);
			dc.type = define_type(dc.stat.st_mode);
			set_display(&d, dc.stat, fich->d_namlen, dc.type[0]);
			d.total += dc.stat.st_blocks;
			sort_select(&sort, &dc, sizeof(dc), d.o);
		}
	}
	print_dir(sort, lst, &d);
}

void	open_dir(char *av, t_list *lst, t_display d)
{
	DIR		*dir;

	dir = opendir(av);
	if (dir == NULL)
	{
		d.o->l_feed++ ? ft_printf("\n") : 0;
		d.o->name++ ? ft_printf("%s:\n", lst->content) : 0;
		ft_putstr_fd("ls: ", 2);
		perror(av);
		return ;
	}
	stockdir(av, dir, lst, d);
	if (closedir(dir) == -1)
	{
		perror(strerror(errno));
		return ;
	}
}
