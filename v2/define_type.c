/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 00:15:21 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/01 00:19:00 by qdegraev         ###   ########.fr       */
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
