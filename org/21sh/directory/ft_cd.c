/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 06:35:21 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/03 06:35:22 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define IS_CD

#include "ft_cd.h"

char		*del_arg(char *args, size_t len)
{
	size_t	i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (args[i] && args[i] != '/')
		i++;
	if (args[i] == '\0')
	{
		return (NULL);
	}
	if (i == len)
		ret = ft_strdup(args + i + 1);
	return (ret);
}

void		set_pwd(t_shell *shell, char *new_pwd)
{
	if (!new_pwd)
		return ;
	ft_strdel(&shell->get_oldpwd);
	shell->get_oldpwd = shell->get_pwd;
	shell->get_pwd = ft_strdup(new_pwd);
	chdir(shell->get_pwd);
}

void		del_path(t_shell *shell, char *args)
{
	int		i;
	char	*tmp;
	char	*del;

	tmp = shell->get_pwd;
	i = ft_strlen(tmp);
	while (i > 0 && shell->get_pwd[i] != '/')
		i--;
	del = ft_strndup(tmp, i);
	if (del[0] == '\0')
		del = ft_strdup("/");
	if (ft_strlen(shell->get_pwd) > 1 && is_dir(shell, del, args, 1))
		set_pwd(shell, del);
	else
		ft_strdel(&del);
}

void		add_path(t_shell *shell, char *args, char *arg)
{
	char *add;

	if (ft_strlen(shell->get_pwd) != 1)
		add = ft_strjoin(ft_strjoin(shell->get_pwd, "/"), arg);
	else
		add = ft_strjoin(shell->get_pwd, arg);
	if (!is_dir(shell, add, NULL, 0))
		add = ft_strjoin(ft_strjoin(shell->get_home, "/"), arg);
	if (is_dir(shell, add, args, 1))
	{
		ft_strdel(&shell->get_oldpwd);
		shell->get_oldpwd = shell->get_pwd;
		shell->get_pwd = add;
		chdir(shell->get_pwd);
	}
	else
		ft_strdel(&add);
}

void		ft_cd(char *args, t_shell *shell)
{
	char	*arg;
	size_t	arg_len;

	if (!args || args[0] == '\0')
		return ;
	args = mod_point(args);
	arg = get_arg(args);
	arg_len = ft_strlen(arg);
	if (arg[0] == '\0' && ft_strlen(args) > 1 && !is_dir(shell, args, args, 1))
		return ;
	if (arg[0] == '\0')
		set_pwd(shell, "/");
	else if ((arg[0] == '~' && arg_len == 1) || (arg[0] == '-' && arg_len == 1))
		set_pwd(shell, arg[0] == '~' ? shell->get_home : shell->get_oldpwd);
	else if (ft_strcmp("/", shell->get_home) != 0 && !is_dir(shell, ft_strjoin(
		ft_strjoin(shell->get_home, "/"), args), args, 0)
		&& !is_dir(shell, ft_strjoin(ft_strjoin(
			shell->get_pwd, "/"), args), args, 1))
		return ;
	else if (!ft_strcmp(arg, ".."))
		del_path(shell, args);
	else if (!is_local(arg))
		add_path(shell, args, arg);
	ft_cd(del_arg(args, arg_len), shell);
}
