/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_n_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:21:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/01 01:27:54 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*print_dir(char *path, t_list *sort, t_list *lst)
{
	t_dircont	d;
	t_dircont	*tmp;
	t_stat		stat;

	while (sort)
	{
		d.path = path[ft_strlen(path) -1] != '/' ? ft_cjoin(ft_strdup(path),
				ft_strdup("/")) : ft_strdup(path);
		d.path = ft_cjoin(d.path, ft_strdup(sort->content));
		lstat(d.path, &stat);
		d.type = define_type(stat.st_mode);
		ft_printf("%-15s Nom : %s\n", d.type, sort->content);
		if (d.type[0] == 'd' && ((char*)sort->content)[0] != '.')
			lst = ft_lst_insert(lst, d.path, ft_strlen(d.path) + 1);
		sort = sort->next;
	}
	return (lst);
}

t_list	*stockdir(char *path, DIR *dir, t_list *lst)
{
	t_dirent	*fich;
	t_stat		stat;
	t_list		*sort;

	while ((fich = readdir(dir)))
		ft_lstadd_back(&sort, fich->d_name, ft_strlen(fich->d_name) + 1);
	sort_list(&sort);
	
	return (lst = print_dir(path, sort, lst));
}

t_list	*open_dir(char *av, t_list *lst)
{
	DIR		*dir = NULL;
	t_list	*temp;
	t_dircont	*tmp;

	dir = opendir(av);
	if (dir == NULL)
	{
		ft_printf("ls: %s: ", av);
		perror("");
		return (lst);
	}
	else
		ft_printf("dossier \" %s \" ouvert avec succes\n", av);
	lst = stockdir(av, dir, lst);
	if (closedir(dir) == -1)
	{
		ft_printf("%s\n", errno);
		return (lst);
	}
	ft_printf("dossier \" %s \" ferme avec succes\n\n\n", av);
	return (lst);
}
