/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 04:47:19 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/06 23:02:38 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static char	*delimitor(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (s + i);
}

static int	first_delimitor(char *s, char c, char **m)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	*m = (s + i);
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		i;
	char	*tmp;
	char	*t;

	if (!s || !(split = (char **)malloc(sizeof(char *) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	t = (char*)s;
	while (t[0])
	{
		if (!(t = delimitor(t, c))[0])
			break ;
		split[i] = ft_strndup(t, first_delimitor(t, c, &tmp));
		t = tmp;
		i++;
	}
	split[i] = NULL;
	return (split);
}
