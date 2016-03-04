/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:24:48 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/04 13:50:14 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <sys/ioctl.h>

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

typedef struct dirent t_dirent;
typedef struct stat t_stat;

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
	char			*name;
	char			*type;
	t_stat			stat;
}					t_dircont;

typedef		struct	s_display
{
	int				len_max;
	int				link_max;
	int				owner_max;
	int				group_max;
	int				size_max;
	int				total;
	t_options		*o;
}					t_display;

/*
** read_n_sort
*/
t_list				*print_dir(t_list *sort, t_list *lst, t_display *d);
t_list				*stockdir(char *path, DIR *dir, t_list *lst, t_display d);
t_list				*open_dir(char *av, t_list *lst, t_display d);

/*
** file type
*/
void				define_permission(char *perm, mode_t st_mode);
char				*define_type(mode_t st_mode);

/*
** lists tools
*/
void				ft_lst_insert(t_list **lst, t_list *in);
void				sort_list(t_list **dir);


void				init_display(t_display *d);
int					ft_num_len(size_t num);

#endif
