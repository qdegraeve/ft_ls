/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:24:48 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/02 23:55:44 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** opendir readdir closedir
*/
# include <sys/types.h>
# include <dirent.h>

/*
** stat lstat
*/
# include <sys/stat.h>
# include <unistd.h>

# include <pwd.h>
# include <grp.h>
# include <time.h>

/*
** errno
*/
# include <errno.h>

/*
** perror
*/
# include <stdio.h>

# include <stdlib.h>
# include "ft_printf/ft_printf.h"

typedef		struct dirent	t_dirent;
typedef		struct stat		t_stat;

typedef		struct	s_options
{
	char			rec;
	char			l;
	char			a;
	char			r;
	char			t;
}					t_options;

typedef		struct	s_dircont
{
	char			*path;
	char			*type;
	int				len_max;
	int				total;
	t_stat			stat;
	t_options		*o;
}					t_dircont;

/*
** read_n_sort
*/
t_list				*print_dir(char *path, t_list *sort, t_list *lst,
		t_dircont d);
t_list				*stockdir(char *path, DIR *dir, t_list *lst, t_dircont d);
t_list				*open_dir(char *av, t_list *lst, t_dircont d);

/*
** file type
*/
void				define_permission(char *perm, mode_t st_mode);
char				*define_type(mode_t st_mode);

/*
** lists tools
*/
t_list				*ft_lst_insert(t_list *lst, void const *content,
		size_t cont_size);
void				sort_list(t_list **dir);

#endif
