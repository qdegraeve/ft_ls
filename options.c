/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 16:18:40 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/11 12:58:16 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_options(t_options *o)
{
	o->name = 0;
	o->l_feed = 0;
	o->rec = 0;
	o->l = 0;
	o->a = 0;
	o->r = 0;
	o->t = 0;
	o->T = 0;
	o->u = 0;
	o->color = 0;
}

void	set_options(char option, t_options *o)
{
	if (option == 'R')
		o->rec = 1;
	else if (option == 'l')
	{
		o->l = 1;
		o->one = 0;
	}
	else if (option == 'a')
		o->a = 1;
	else if (option == 'r')
		o->r = 1;
	else if (option == 't')
		o->t = 1;
	else if (option == 'T')
		o->T = 1;
	else if (option == 'u')
		o->u = 1;
	else if (option == '1')
	{
		o->l = 0;
		o->one = 1;
	}
	else
	{
		ft_printf("ls: illegal option -- %c\n", option);
		ft_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]");
		ft_printf(" [file ...]\n");
		exit(EXIT_FAILURE);
	}
}

int		check_options(char **av, t_options *o)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strcmp(av[i], "--") == 0)
			return (i + 1);
		else if (av[i][1] == '\0')
			return (i);
		j = 1;
		while (av[i][j])
		{
			set_options(av[i][j], o);
			j++;
		}
		i++;
	}
	return (i);
}
