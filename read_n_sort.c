/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_n_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:21:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/04 13:50:48 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_num_len(size_t num)
{
	int		i;

	i = 0;
	if (num == 0)
		return (0);
	while ((num = num / 10))
		i++;
	return (i + 1);
}

int		ft_isnavdir(char *name)
{
	if (!name)
		return (0);
	if (name[0] == '.' && (!name[1] || name[1] == '.'))
		return (1);
	else
		return (0);
}

int		ft_ishidden(char *name)
{
	if (!name)
		return (0);
	if (name[0] == '.' && !ft_isnavdir(name))
		return (1);
	else
		return (0);
}

void	display_long(t_dircont *dc, t_display *d)
{
	time_t t;

	ft_printf("%-12s", dc->type);
	ft_printf("%-*d ", d->link_max, dc->stat.st_nlink);
	ft_printf("%-*s  ", d->owner_max, (getpwuid(dc->stat.st_uid))->pw_name);
	ft_printf("%-*s  ", d->group_max, (getgrgid(dc->stat.st_gid))->gr_name);
	ft_printf("%*d ", d->size_max, dc->stat.st_size);
	t = dc->stat.st_mtime;
	ft_printf("%-.12s ", ctime(&t) + 4);
	ft_printf("%-*s \n", d->len_max, dc->name);
}

t_list	*print_dir(t_list *sort, t_list *lst, t_display *d)
{
	t_list *tmp = NULL;
	t_dircont	*dc;
	
	//ft_printf("print enter\n");
	//ft_printf("print enter 2\n");
	d->o->l ? ft_printf("total %d\n", d->total) : 0;
//	ft_printf("print enter 3\n");
	while (sort)
	{
//		ft_printf("print boucle sort\n");
		dc = sort->content;
		if (d->o->l)
			display_long(dc, d);
		else
			ft_printf("%-*s\n", d->len_max, dc->name);
		if (d->o->rec && dc->type[0] == 'd' && ft_isnavdir(dc->name) == 0)
			!d->o->a && ft_ishidden(dc->name) ? 0 :
					ft_lstadd_back(&tmp, dc->path, ft_strlen(dc->path) + 1);
		sort = sort->next;
	}
//	ft_printf("print before insert\n");
	tmp ? ft_lst_insert(&lst, tmp) : 0;
//	ft_printf("print after insert\n");
	return (lst);
}

void	set_display(t_display *d, t_stat stat, int namlen)
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

}

t_list	*stockdir(char *path, DIR *dir, t_list *lst, t_display d)
{
	t_dirent	*fich;
	t_list		*sort;
	t_dircont	dc;

	init_display(&d);
	while ((fich = readdir(dir)))
	{
//		ft_printf("stock boucle\n");
		dc.path = ft_strjoin(path, "/");
		dc.path = ft_cjoin(dc.path, ft_strdup(fich->d_name));
		lstat(dc.path, &dc.stat);
		dc.name = ft_strdup(fich->d_name);
		dc.type = define_type(dc.stat.st_mode);
		!d.o->a && ((char*)fich->d_name)[0] == '.' ? 0 : set_display(&d, dc.stat, fich->d_namlen);
		d.total += !d.o->a && ((char*)fich->d_name)[0] == '.' ? 0 :
			dc.stat.st_blocks;
		!d.o->a && ((char*)fich->d_name)[0] == '.' ? 0 : 
			ft_lstadd_back(&sort, &dc, sizeof(dc));
//		ft_strdel(&d.type);
//		ft_strdel(&d.name);
//		ft_strdel(&d.path);
	}
//	ft_printf("stock before sort\n");
	sort_list(&sort);
//	ft_printf("stock after sort\n");
	return (lst = print_dir(sort, lst, &d));
}

t_list	*open_dir(char *av, t_list *lst, t_display d)
{
	DIR		*dir;

	dir = opendir(av);
	if (dir == NULL)
	{
		ft_printf("ls: %s: ", av);
		perror("");
		return (lst);
	}
	lst = stockdir(av, dir, lst, d);
	if (closedir(dir) == -1)
	{
		ft_printf("%s\n", errno);
		return (lst);
	}
	return (lst);
}
