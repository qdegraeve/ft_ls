/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_n_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:21:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/04 20:21:36 by qdegraev         ###   ########.fr       */
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
	char buff[500];
	int i;

	i = 0;
	ft_printf("%-12s", dc->type);
	ft_printf("%-*d ", d->link_max, dc->stat.st_nlink);
	ft_printf("%-*s  ", d->owner_max, (getpwuid(dc->stat.st_uid))->pw_name);
	ft_printf("%-*s  ", d->group_max, (getgrgid(dc->stat.st_gid))->gr_name);
	ft_printf("%*d ", d->size_max, dc->stat.st_size);
	if (ft_abs(time(NULL) - (t = dc->stat.st_mtime)) > 15778463)
	{
		ft_printf("%-.7s ", ctime(&t) + 4);
		ft_printf("%-.4s ", ctime(&t) + 20);
	}
	else
		ft_printf("%-.12s ", ctime(&t) + 4);
	ft_printf("%-s", dc->name);
	if (dc->type[0] == 'l' && (i = readlink(dc->path, buff, 500)))
	{
		buff[i] = '\0';
		ft_printf(" -> %s\n", buff);
	}
	else
		ft_printf("\n");
}

void	print_dir(t_list *sort, t_list *lst, t_display *d)
{
	t_list *tmp = NULL;
	t_dircont	*dc;

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
		sort = sort->next;
	}
	tmp ? ft_lst_insert(&lst, tmp) : 0;
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

void	stockdir(char *path, DIR *dir, t_list *lst, t_display d)
{
	t_dirent	*fich;
	t_list		*sort;
	t_dircont	dc;

	init_display(&d);
	while ((fich = readdir(dir)))
	{
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
	}
	sort_list(&sort, d.o);
	d.o->t ? sort_list_time(&sort, d.o) : 0;
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
