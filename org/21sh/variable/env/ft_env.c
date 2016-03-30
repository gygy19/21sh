/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:00:41 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/03 20:14:51 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "struct.h"
#include "libft.h"
#include "all.h"

void		print_env(t_env *env, t_shell *shell)
{
	while (env != NULL)
	{
		ft_putstr(env->name);
		ft_putstr("=");
		if (ft_strcmp(env->name, "PWD") == 0)
			ft_putstr(shell->get_pwd);
		else if (ft_strcmp(env->name, "OLDPWD") == 0)
			ft_putstr(shell->get_oldpwd);
		else
			ft_putstr(env->value);
		ft_putstr("\n");
		env = env->right;
	}
}

t_env		*create_total_env(t_env *env, char **c_env)
{
	int		i;
	int		i2;
	t_env	*tmp;
	int		first;
	t_env	*left;

	i = 0;
	first = 1;
	left = NULL;
	while (c_env[i])
	{
		i2 = 0;
		while (c_env[i][i2] && c_env[i][i2] != '=')
			i2++;
		env = create_env(left, ft_strndup(c_env[i], i2), get_v(c_env[i], i2));
		if (first-- > 0)
			tmp = env;
		left = env;
		env = env->right;
		i++;
	}
	return (tmp);
}

void		unset_env(t_env *env, char *name)
{
	if (ft_strcmp(name, "PWD") == 0 || ft_strcmp(name, "OLDPWD") == 0
		|| ft_strcmp(name, "PATH") == 0)
	{
		return ;
	}
	while (env != NULL)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			if (env->right != NULL && env->left != NULL)
				env->left->right = env->right;
			if (env->right != NULL && env->left != NULL)
				env->right->left = env->left;
			else if (env->left != NULL)
				env->left->right = NULL;
			else if (env->right != NULL)
				env->right->left = NULL;
			ft_strdel(&env->name);
			ft_strdel(&env->value);
			free(env);
			return ;
		}
		env = env->right;
	}
}

void		set_env(t_env *env, char *name, char *value, t_shell *shell)
{
	int		bol;
	t_env	*tmp;

	bol = 0;
	value = verif_env(name, value, shell);
	if (!value)
		return ;
	while (env != NULL)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			if (ft_strcmp(name, "PATH") == 0)
				create_shell(NULL)->path = ft_strdup(value);
			if (ft_strcmp(name, "HOME") == 0)
				create_shell(NULL)->home = ft_strdup(value);
			ft_strdel(&env->value);
			env->value = value == NULL ? ft_strnew(1) : value;
			bol = 1;
		}
		if (env->right == NULL)
			tmp = env;
		env = env->right;
	}
	if (bol == 0)
		env = create_env(tmp, name, value);
}

t_env		*create_env(t_env *left, char *name, char *value)
{
	t_env	*new;

	if (!(new = (t_env*)malloc(sizeof(t_env))))
		print_error_malloc("[add_env] t_env");
	new->left = NULL;
	new->right = NULL;
	if (left != NULL)
	{
		new->left = left;
		left->right = new;
	}
	if (ft_strcmp(name, "HOME") == 0 && !is_directory(value))
		value = ft_strdup("/");
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	if (ft_strcmp(name, "SHLVL") == 0)
		new->value = ft_itoa(ft_atoi(new->value) + 1);
	return (new);
}
