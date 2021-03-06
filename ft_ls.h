/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:24:48 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/13 15:09:14 by qdegraev         ###   ########.fr       */
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
	char			up_t;
	char			u;
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
** options
*/
void				init_options(t_options *o);
void				set_options(char option, t_options *o);
int					check_options(char **av, t_options *o);

/*
** get_argv
*/
void				print_params(t_list *tmp, t_list **lst, t_display *d);
void				filter_params(t_list *sort, t_list **lst, t_display *d);
void				sort_params(char **av, t_list **lst, t_options *o,
		t_display d);

/*
** read_n_sort
*/
void				print_dir(t_list *sort, t_list *lst, t_display *d);
void				stockdir(char *path, DIR *dir, t_list *lst, t_display d);
void				open_dir(char *av, t_list *lst, t_display d);
void				set_display(t_display *d, t_stat stat, int namlen,
		char type);

/*
** print
*/
void				color(t_dircont *dc);
void				print_size(t_dircont *dc, t_display *d);
void				print_owner_group(t_dircont *dc, t_display *d);
void				print_time(t_dircont *dc, t_display *d);
void				display_long(t_dircont *dc, t_display *d);

/*
** file type
*/
void				define_permission(char *perm, mode_t st_mode);
char				*define_type(mode_t st_mode);

/*
** lists tools
*/
void				sort_select(t_list **dir, void *content, size_t cont_size,
		t_options *o);
void				sort_list(t_list **dir, int o,
		int (*sort)(t_dircont *, void *, int));
int					sort_ascii(t_dircont *c1, void *c2, int o);
int					sort_mod_time(t_dircont *c1, void *c2, int o);
int					sort_access_time(t_dircont *c1, void *c2, int o);

/*
** Mr Proper
*/
void				ft_lst_sortinsert(t_list **beg_lst, t_list *new, int o,
		int (*sort)(t_dircont *, void *, int));
void				ft_lst_insert(t_list **lst, t_list *in);
void				lst_delone(t_list **lst, void (*del)(void *));
void				del_dircont(void *to_del);
void				del_string(void *to_del);

/*
** tools
*/
void				init_display(t_display *d);
int					ft_num_len(size_t num);
int					ft_isnavdir(char *name);
int					ft_ishidden(char *name);

#endif
