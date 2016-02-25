/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:24:48 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/25 18:46:16 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
 * opendir readdir closedir
*/
# include <sys/types.h>
# include <dirent.h>

/*
 * stat lstat
*/
#include <sys/stat.h>
#include <unistd.h>

/*
 * errno
*/
# include <errno.h>

/*
 * perror
*/
#include <stdio.h>

#include <stdlib.h> 
#include "ft_printf/ft_printf.h"

typedef		struct dirent t_dirent;
typedef		struct stat t_stat;

typedef		struct	s_dircont
{
	t_dirent		*fich;
	t_stat			stat;
}					t_dircont;

#endif
