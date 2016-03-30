/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 00:20:25 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/02 00:20:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include <unistd.h>

static char	*delimitor(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (s + i);
}

static int	pros(char *s, int n, int c)
{
	int i;
	int	in;

	i = 0;
	in = 0;
	while (s[i] && s[n] == c)
	{
		if (in && s[(i > 1) ? i - 1 : 0] != '\\' && s[i] == in)
			in = 0;
		else if ((!in && s[(i > 1) ? i - 1 : 0] != '\\' && s[i] == '\'')
			|| (!in && s[(i > 1) ? i - 1 : 0] != '\\' && s[i] == '{')
			|| (!in && s[(i > 1) ? i - 1 : 0] != '\\' && s[i] == '(')
			|| (!in && s[(i > 1) ? i - 1 : 0] != '\\' && s[i] == '\"')
			|| (!in && s[(i > 1) ? i - 1 : 0] != '\\' && s[i] == '`'))
			in = s[i];
		if (i == n && !in)
			return (1);
		i++;
	}
	return (0);
}

static int	first_delimitor(char *s, char c, char **m, int f(char *, int, int))
{
	int		i;

	i = 0;
	while (s[i] && !f(s, i, c))
		i++;
	*m = (s + i);
	return (i);
}

char		**ft_split_process(char const *s, char c)
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
		split[i] = ft_strndup(t, first_delimitor(t, c, &tmp, pros));
		t = tmp;
		i++;
	}
	split[i] = NULL;
	return (split);
}
