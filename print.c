/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 01:52:30 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/08 20:57:08 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	color(t_dircont *dc)
{
	if (dc->type[0] == '-')
		ft_printf("%-s", dc->name);
	else if (dc->type[0] == 'd')
		ft_printf("\033[36m%-s\033[0m", dc->name);
	else if (dc->type[0] == 'l')
		ft_printf("\033[35m%-s\033[0m", dc->name);
	else if (dc->type[0] == 'p')
		ft_printf("%-s", dc->name);
	else if (dc->type[0] == 'b')
		ft_printf("\033[7;34;36m%-s\033[0m", dc->name);
	else if (dc->type[0] == 'l')
		ft_printf("%-s", dc->name);
	else if (dc->type[0] == 'c')
		ft_printf("\033[27;34;43m%-s\033[0m", dc->name);
}

void	print_size(t_dircont *dc, t_display *d)
{
	if (dc->type[0] == 'c' || dc->type[0] == 'b')
		ft_printf("%3d,%*d ", major(dc->stat.st_rdev), d->size_max > 4 ?
				d->size_max : 4, minor(dc->stat.st_rdev));
	else if (d->sys)
		ft_printf("%*d ", d->size_max > 4 ? d->size_max + 4 : 8
				, dc->stat.st_size);
	else
		ft_printf("%*d ", d->size_max, dc->stat.st_size);
}

void	print_owner_group(t_dircont *dc, t_display *d)
{
	char *name;

	if (!(name = (getpwuid(dc->stat.st_uid))->pw_name))
		ft_printf("%-*d  ", d->owner_max, dc->stat.st_uid);
	else
		ft_printf("%-*s  ", d->owner_max, (getpwuid(dc->stat.st_uid))->pw_name);
	if (!(name = (getgrgid(dc->stat.st_gid))->gr_name))
		ft_printf("%-*d  ", d->owner_max, dc->stat.st_uid);
	else
		ft_printf("%-*s  ", d->group_max, (getgrgid(dc->stat.st_gid))->gr_name);
}

void	print_time(t_dircont *dc, t_display *d)
{
	time_t	t;

	if (d->o->T)
		ft_printf("%-.20s ", ctime(&t) + 4);
	else if (time(NULL) - (t = dc->stat.st_mtime) > 15778463 || t > time(NULL))
	{
		ft_printf("%-.7s ", ctime(&t) + 4);
		ft_printf("%-.4s ", ctime(&t) + 20);
	}
	else
		ft_printf("%-.12s ", ctime(&t) + 4);
}

void	display_long(t_dircont *dc, t_display *d)
{
	char	*buff;
	int		i;

	i = 0;
	buff = (char*)malloc(1024);
	ft_printf("%-12s", dc->type);
	ft_printf("%-*d ", d->link_max, dc->stat.st_nlink);
	print_owner_group(dc, d);
	print_size(dc, d);
	print_time(dc, d);
	d->o->color ? color(dc) : ft_printf("%-s", dc->name);
	if (dc->type[0] == 'l' && (i = readlink(dc->path, buff, 1024)))
	{
		buff[i] = '\0';
		ft_printf(" -> %s\n", buff);
	}
	else
		ft_printf("\n");
	ft_strdel(&buff);
}
