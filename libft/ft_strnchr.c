/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 03:18:48 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/07 03:57:36 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnchr(char const *s, int c, int nbr)
{
	char	*tmp;
	int		i;

	tmp = (char*)s;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			nbr--;
			if (nbr == 0)
				return (i);
		}
		i++;
	}
	return (0);
}
