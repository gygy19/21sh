/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 21:24:45 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/12 21:24:47 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "all.h"
#include "libft.h"
#include "ft_cd.h"

char		**get_env(t_env *env)
{
	t_env	*tmp;
	int		i;
	char	**ret;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->right;
	}
	if (!(ret = malloc(sizeof(char *) * (i + 1))))
		print_error_malloc("[get_env] char **");
	tmp = env;
	i = 0;
	while (tmp)
	{
		ret[i++] = ft_strjoin(ft_strjoin(tmp->name, "="), tmp->value);
		tmp = tmp->right;
	}
	ret[i] = NULL;
	return (ret);
}

char		*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
			return (env->value);
		env = env->right;
	}
	return (NULL);
}

t_env		*get_end_env(t_env *env)
{
	t_env *end;

	if (!env)
		return (NULL);
	end = env;
	while (end->right)
		end = end->right;
	return (end);
}

char		*verif_env(char *name, char *value, t_shell *shell)
{
	char	**tmp;
	int		i;

	i = 0;
	if (ft_strcmp(name, "PWD") == 0 || ft_strcmp(name, "OLDPWD") == 0
		|| ft_strcmp(name, "HOME") == 0 || ft_strcmp(name, "TMPDIR") == 0)
	{
		tmp = ft_strsplit(value, ':');
		if (!is_directory(value))
			return (NULL);
		else if (ft_strcmp(name, "HOME") != 0 && ft_strcmp(name, "OLDPWD") != 0)
		{
			ft_cd(value, shell);
			return (value[0] == '/' ? value : ft_strdup(shell->get_pwd));
		}
	}
	return (value);
}
