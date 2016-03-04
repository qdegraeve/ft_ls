/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:31:35 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/04 13:05:25 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_display(t_display *d)
{
	d->len_max = 0;
	d->link_max = 0;
	d->owner_max = 0;
	d->group_max = 0;
	d->size_max = 0;
	d->total = 0;

}

void	init_options(t_options *o)
{
	o->rec = 0;
	o->l = 0;
	o->a = 0;
	o->r = 0;
	o->t = 0;
}

int		check_options(char **av, t_options *o, t_list **lst)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (av[i] && av[i][0] == '-')
	{
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] == 'R')
				o->rec = 1;
			else if (av[i][j] == 'l')
				o->l = 1;
			else if (av[i][j] == 'a')
				o->a = 1;
			else if (av[i][j] == 'r')
				o->r = 1;
			else if (av[i][j] == 't')
				o->t = 1;
			else
			{
				ft_lstadd_back(lst, av[i] + j, ft_strlen(av[i] + j));
				break ;
			}
			j++;
		}
		i++;
	}
	return (i);
}

int		main(int ac, char **av)
{
	int			i;
	t_options	o;
	t_display	d;
	t_list		*lst;

	lst = NULL;
	init_options(&o);
	if ((i = check_options(av, &o, &lst)) == ac)
		ft_lstadd_back(&lst, "./", 3);
	d.o = &o;
	while (av[i])
		lst =  open_dir(ft_strdup(av[i++]), lst, d);
	i = 0;
	while (lst)
	{
		i++ == 0 ? 0 : ft_printf("\n%s:\n", lst->content);
		open_dir(lst->content, lst, d);
		lst = lst->next;
	}
	return (0);
}
