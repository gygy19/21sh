/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 03:35:21 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/09 03:35:23 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "all.h"
#include "libft.h"
#include "ft_cd.h"

char		*get_v(char *env, int start)
{
	char	*tmp;

	tmp = env + (start + 1);
	return (ft_strndup(tmp, ft_strlen(tmp)));
}

DIR			*open_directory(char *dir)
{
	DIR *dirp;

	dirp = NULL;
	dirp = opendir(dir);
	return (dirp);
}

int			is_directory(char *file)
{
	DIR *dirp;

	dirp = NULL;
	if (!file)
		return (0);
	dirp = opendir(file);
	if (dirp == NULL)
		return (0);
	closedir(dirp);
	return (1);
}

void		print_user(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, "USER") == 0)
		{
			ft_putstr(env->value != NULL ? env->value : 0);
			ft_putstr("\n");
			return ;
		}
		env = env->right;
	}
}

int			is_exe2(char *dir, char *file, t_shell *shell)
{
	int			ret;
	char		*infos;
	struct stat *stats;

	ret = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[is_exe] struct stat");
	infos = ft_strjoin(ft_strjoin(dir, "/"), file);
	if (lstat(infos, stats) != 0 || (file[0] != '.' && file[1] != '/'))
		return (1);
	if (is_directory(infos))
		ret = 2;
	else if ((stats->st_mode & S_IXUSR) && (stats->st_mode & S_IXGRP)
		&& (stats->st_mode & S_IXOTH))
		ret = 1;
	if (ret == 0)
	{
		ft_putstr_fd("21sh: permission denied: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (ret == 2 && !(ret = 0))
		ft_cd(file, shell);
	ft_strdel(&infos);
	return (ret);
}
