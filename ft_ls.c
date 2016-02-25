/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:31:35 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/25 18:52:23 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*t_stat	*get_stat(t_list *lst)
{
	t_stat	*stat;

}*/

int main(int ac, char**av)
{
	DIR			*dir = NULL;
	t_dirent	*fich = NULL;
	t_dircont	d;
	t_dircont	*tmp;
	t_list		*lst = NULL;
	char *path;

	if (ac > 2)
	{
		ft_printf("erreur il faut un seul argument et pas %d\n", ac - 1);
		return (0);
	}
	dir = ac == 2 ? opendir(av[1]) : opendir("./");
	if (dir == NULL)
	{
		ft_printf("ls: %s: ", av[1]);
		perror("");
		//ft_printf("le dossier n'existe pas\n");
		return (0);
	}
	else
		ft_printf("dossier ouvert avec succes\n");
	while ((d.fich = readdir(dir)))
	{
		stat(d.fich->d_name, &d.stat);
		ft_lstadd_back(&lst, &d, sizeof(d));
	}
	while (lst)
	{
		tmp = lst->content;
		ft_printf("Nom : %s \nlongueur : %d\ntype : %-10s\n\n", tmp->fich->d_name, tmp->fich->d_namlen, (S_ISREG(tmp->stat.st_mode)) ?  "regular" :
				(S_ISDIR(tmp->stat.st_mode)) ?  "directory" :
				(S_ISFIFO(tmp->stat.st_mode)) ? "FIFO" :
				(S_ISSOCK(tmp->stat.st_mode)) ? "socket" :
				(S_ISLNK(tmp->stat.st_mode)) ?  "symlink" :
				(S_ISBLK(tmp->stat.st_mode)) ?  "block dev" :
				(S_ISCHR(tmp->stat.st_mode)) ?  "char dev" : "???");
		lst = lst->next;
	}

	if (closedir(dir) == -1)
	{
		ft_printf("%s\n", errno);
		return (0);
	}
	ft_printf("dossier ferme avec succes\n");
	return (0);
}
