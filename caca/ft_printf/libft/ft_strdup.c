/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 17:51:56 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/26 17:52:28 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*str;

	if (src == NULL)
		return (NULL);
	if (!(str = ft_strnew(ft_strlen(src))))
		return (NULL);
	ft_strcpy(str, src);
	return (str);
}
