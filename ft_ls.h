/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:24:48 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/08 02:00:11 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/ioctl.h>

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

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct		s_options
{
	int				l_feed;
	int				name;
	char			rec;
	char			l;
	char			a;
	char			r;
	char			t;
	char			one;
	char			color;
}					t_options;

typedef struct		s_dircont
{
	char			*path;
	char			*name;
	char			*type;
	t_stat			stat;
}					t_dircont;

typedef struct		s_display
{
	int				sys;
	int				len_max;
	int				link_max;
	int				owner_max;
	int				group_max;
	int				size_max;
	int				total;
	t_options		*o;
}					t_display;

/*
** print
*/
void				color(t_dircont *dc);
void				print_size(t_dircont *dc, t_display *d);
void				print_owner_group(t_dircont *dc, t_display *d);
void				print_time(t_dircont *dc);
void				display_long(t_dircont *dc, t_display *d);

/*
** read_n_sort
*/
void				print_dir(t_list *sort, t_list *lst, t_display *d);
void				stockdir(char *path, DIR *dir, t_list *lst, t_display d);
void				open_dir(char *av, t_list *lst, t_display d);
void				set_display(t_display *d, t_stat stat, int namlen,
		char type);

/*
** file type
*/
void				define_permission(char *perm, mode_t st_mode);
char				*define_type(mode_t st_mode);

/*
** lists tools
*/
void				ft_lst_insert(t_list **lst, t_list *in);
void				sort_list(t_list **dir, t_options *o);
void				sort_list_time(t_list **dir, t_options *o);

/*
** tools
*/
void				init_display(t_display *d);
int					ft_num_len(size_t num);
int					ft_isnavdir(char *name);
int					ft_ishidden(char *name);
void				del_listone(t_list **sort);

#endif
