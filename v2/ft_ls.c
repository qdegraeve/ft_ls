/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:31:35 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/01 01:27:58 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_options(t_options	*o)
{
	o->rec = 0;
	o->l = 0;
	o->a = 0;
	o->r = 0;
	o->t = 0;
}

int		check_options(char **av, t_options *o, t_list **lst)
{
	int i;
	int j;

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

int main(int ac, char**av)
{
	int		i;
	t_options	o;
	t_list	*lst = NULL;

	init_options(&o);
	i = check_options(av, &o, &lst);
	while (av[i])
	{
		lst = ac == 1 ? open_dir(ft_strdup("./"), lst) : i == 0 ? 0 :
			open_dir(ft_strdup(av[i]), lst);
		while (lst)
		{
			ft_printf("\t\tpath = %s\n", lst->content);
			open_dir(lst->content, lst);
			lst = lst->next;
		}
		if (ac == 1)
			break;
		i++;
	}
	return (0);
}
