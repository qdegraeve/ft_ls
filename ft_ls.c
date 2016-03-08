/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:31:35 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/08 18:12:38 by qdegraev         ###   ########.fr       */
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
	d->sys = 0;
}

int		main(int ac, char **av)
{
	int			i;
	t_options	o;
	t_display	d;
	t_list		*lst;

	lst = NULL;
	init_options(&o);
	if ((i = check_options(av, &o)) == ac)
		ft_lstadd_back(&lst, ".", 2);
	else
	{
		i + 1 < ac ? o.name++ : 0;
		sort_params(av + i, &lst, &o, d);
	}
	d.o = &o;
	while (lst)
	{
		open_dir(lst->content, lst, d);
		lst_delone(&lst, del_string);
	}
	return (0);
}
