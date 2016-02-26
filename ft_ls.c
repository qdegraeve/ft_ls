/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:31:35 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/26 19:53:41 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	define_permission(char *perm, mode_t st_mode)
{
	int		i;

	i = 0;
	S_IRUSR & st_mode ? perm[++i] = 'r' : perm[++i];
	S_IWUSR & st_mode ? perm[++i] = 'w' : perm[++i];
	S_IXUSR & st_mode ? perm[++i] = 'x' : perm[++i];
	S_IRGRP & st_mode ? perm[++i] = 'r' : perm[++i];
	S_IWGRP & st_mode ? perm[++i] = 'w' : perm[++i];
	S_IXGRP & st_mode ? perm[++i] = 'x' : perm[++i];
	S_IROTH & st_mode ? perm[++i] = 'r' : perm[++i];
	S_IWOTH & st_mode ? perm[++i] = 'w' : perm[++i];
	S_IXOTH & st_mode ? perm[++i] = 'x' : perm[++i];
}

char	*define_type(mode_t st_mode)
{
	char	*type;
	
	type = ft_strdup("----------");
	if (S_ISREG(st_mode))
		*type = '-';
	else if (S_ISDIR(st_mode))
		*type = 'd';
	else if (S_ISFIFO(st_mode))
		*type = 'p';
	else if (S_ISSOCK(st_mode))
		*type = 's';
	else if (S_ISLNK(st_mode))
		*type = 'l';
	else if (S_ISBLK(st_mode))
		*type = 'b';
	else if (S_ISCHR(st_mode))
		*type = 'c';
	else
		*type = '?';
	define_permission(type, st_mode);
return (type);
}


t_list	*printdir(char *path, DIR *dir, t_list *lst)
{
	char	*type;
	t_dircont	d;
	t_dircont	*tmp;
	char *pat;

	pat = NULL;
	while ((d.fich = readdir(dir)))
	{
		pat = path[ft_strlen(path) -1] != '/' ? ft_cjoin(ft_strdup(path), ft_strdup("/")) : ft_strdup(path);
		pat = ft_cjoin(pat, ft_strdup(d.fich->d_name));
		lstat(pat, &d.stat);
		type = define_type(d.stat.st_mode);
		ft_printf("%-15s Nom : %s\n", type, d.fich->d_name);
		if (type[0] == 'd' && d.fich->d_name[0] != '.')
			ft_lstadd_back(&lst, pat, ft_strlen(pat) + 1);
		ft_strdel(&pat);
		ft_strdel(&type);
	}
	return (lst);
}

t_list	*read_args(char *av, t_list *lst)
{
	int i = 0;
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
	lst = printdir(ft_strdup(av), dir, lst);
	//	ft_printf("caca[%d]\n", i++);
	if (closedir(dir) == -1)
	{
		ft_printf("%s\n", errno);
		return (lst);
	}
	ft_printf("dossier \" %s \" ferme avec succes\n\n\n", av);
	return (lst);
}

int main(int ac, char**av)
{
	int		i;
	t_dircont	*tmp;
	t_list	*lst = NULL;

	i = 0;
	while (av[i])
	{
		lst = ac == 1 ? read_args("./", lst) : i == 0 ? 0 : read_args(av[i], lst);
		while (lst)
		{
			ft_printf("\t\tliste name = %s\n", lst->content);
			read_args(lst->content, lst);
			lst = lst->next;
		}
		if (ac == 1)
			break;
		i++;
	}
	return (0);
}
