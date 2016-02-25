/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:31:35 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/24 19:06:25 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int ac, char**av)
{
	DIR			*dir = NULL;
	t_dirent	*fich = NULL;
	t_stat		caca;
	char		*path = NULL;
	char		*tmp;


	if (ac != 2)
	{
		ft_printf("erreur il faut un seul argument et pas %d\n", ac - 1);
		return (0);
	}
	dir = opendir(av[1]);
	if (dir == NULL)
	{
		ft_printf("ls: %s: ", av[1]);
		perror("");
		//ft_printf("le dossier n'existe pas\n");
		return (0);
	}
	else
		ft_printf("dossier ouvert avec succes\n");
	path = av[1][ft_strlen(av[1]) -1] == '/' ? ft_strdup(av[1]) : ft_cjoin(ft_strdup(av[1]), ft_strdup("/"));
	while ((fich = readdir(dir)))
	{
		tmp = ft_strjoin(path, ft_strdup(fich->d_name));
		stat(path, &caca);
		ft_printf("%s de longueur : %lu\n", fich->d_name, fich->d_namlen);
		ft_printf("inoeud = {%d}\n", caca.st_ino);
		free(tmp);
	}

	if (closedir(dir) == -1)
	{
		ft_printf("%s\n", errno);
		return (0);
	}
		ft_printf("dossier ferme avec succes\n");
	return (0);
}
