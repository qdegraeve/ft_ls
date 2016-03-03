/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_n_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:21:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/03 20:18:20 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	display_long(t_stat stat, t_dircont d, char *name)
{
	time_t t;

	ft_printf("%-12s", d.type);
	ft_printf("%-2d", stat.st_nlink);
	ft_printf("%-s  ", (getpwuid(stat.st_uid))->pw_name);
	ft_printf("%-s ", (getgrgid(stat.st_gid))->gr_name);
	ft_printf("%6ld ", stat.st_size);
	t = stat.st_mtime;
	ft_printf("%-.12s ", ctime(&t) + 4);
	ft_printf("%-*s \n", d.len_max, name);
}

t_list	*print_dir(char *path, t_list *sort, t_list *lst, t_dircont d)
{
	t_list *tmp = NULL;
	
	d.o->l ? ft_printf("total %d\n", d.total) : 0;
	while (sort)
	{
		d.path = ft_strjoin(path, "/");
		d.path = ft_cjoin(d.path, ft_strdup(sort->content));
		lstat(d.path, &d.stat);
		d.type = define_type(d.stat.st_mode);
		if (d.o->l)
			display_long(d.stat, d, sort->content);
		else
			ft_printf("%-*s\n", d.len_max, sort->content);
		if (d.o->rec && d.type[0] == 'd' && ft_isnavdir(sort->content) == 0)
			!d.o->a && ft_ishidden(sort->content) ? 0 :
					ft_lstadd_back(&tmp, d.path, ft_strlen(d.path) + 1);
		ft_strdel(&d.type);
		ft_strdel(&d.path);
		sort = sort->next;
	}
	tmp ? ft_lst_insert(&lst, tmp) : 0;
	return (lst);
}

t_list	*stockdir(char *path, DIR *dir, t_list *lst, t_dircont d)
{
	t_dirent	*fich;
	t_list		*sort;

	d.len_max = 0;
	while ((fich = readdir(dir)))
	{
		d.path = ft_strjoin(path, "/");
		d.path = ft_cjoin(d.path, ft_strdup(fich->d_name));
		lstat(d.path, &d.stat);
		!d.o->a && ((char*)fich->d_name)[0] == '.' ? 0 :
			ft_lstadd_back(&sort, fich->d_name, fich->d_namlen + 1);
		if (d.len_max < fich->d_namlen)
			d.len_max = fich->d_namlen;
		d.total += !d.o->a && ((char*)fich->d_name)[0] == '.' ? 0 :
			d.stat.st_blocks;
	}
	sort_list(&sort);
	return (lst = print_dir(path, sort, lst, d));
}

t_list	*open_dir(char *av, t_list *lst, t_dircont d)
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
