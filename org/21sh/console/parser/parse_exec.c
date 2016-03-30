/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 22:59:31 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/26 22:59:34 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "ft_cd.h"
#include "all.h"
#include "sig.h"

int			is_exe(char *dir, char *file)
{
	int			ret;
	char		*infos;
	struct stat *stats;

	ret = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[is_exe] struct stat");
	infos = ft_strjoin(ft_strjoin(dir, "/"), file);
	lstat(infos, stats);
	if (is_directory(infos))
		ret = 2;
	else if ((stats->st_mode & S_IXUSR) && (stats->st_mode & S_IXGRP)
		&& (stats->st_mode & S_IXOTH))
		ret = 1;
	ft_strdel(&infos);
	return (ret == 2 ? 0 : ret);
}

char		*get_exename(t_tree *tree, char *path, t_shell *shell)
{
	char	*exe;

	(void)shell;
	if (path == NULL)
		return (0);
	if (ft_strncmp(path, tree->args[0], ft_strlen(path)) != 0)
		exe = ft_strjoin(path, ft_strjoin("/", tree->args[0]));
	else
		exe = tree->args[0];
	return (exe);
}

char		*modif_dir(t_tree *tree)
{
	char	*tmp;

	if (tree->args[0][0] != '.' && tree->args[0][1] != '/')
	{
		tmp = ft_strjoin("./", tree->args[0]);
		ft_strdel(&tree->args[0]);
		tree->args[0] = tmp;
	}
	return (tree->args[0]);
}

t_st		*create_st(void)
{
	t_st	*st;

	if (!(st = (t_st*)malloc(sizeof(t_st))))
		return (NULL);
	st->fd[0] = 0;
	st->fd[1] = 0;
	st->fd2[0] = 0;
	st->fd2[1] = 0;
	return (st);
}
