/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 03:29:17 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/10 03:29:20 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "ft_cd.h"
#include "all.h"
#include "sig.h"

int			sub_pipe_write(t_tree *tree, int ant)
{
	char	buff[4097];
	int		ret;

	ret = read(tree->left->st->fd[0], buff, 4096);
	close(tree->left->st->fd[0]);
	close(tree->left->st->fd[1]);
	if (pipe(tree->st->fd2) == -1)
		return (0);
	write(tree->st->fd2[1], buff + ant, ret - ant);
	close(tree->st->fd2[1]);
	return (1);
}

int			exec_cmd_write_end_pipe(int fd, t_tree *tree,
	char *path, t_shell *shell)
{
	char	*exe;

	if (path == NULL || fd <= 0)
		return (0);
	if (!(exe = get_exename(tree, path, shell)))
		return (0);
	tree->st = create_st();
	if (sub_pipe_write(tree, 1) == 0)
		return (0);
	if (tree->args[0][0] != '.' && tree->args[0][1] != '/')
		tree->args[0] = ft_strjoin("./", tree->args[0]);
	if ((tree->pid = fork()) == 0)
	{
		if (dup2(tree->left->st->fd[0], 0) == -1)
			return (0);
		if (dup2(fd, 1) == -1)
			return (0);
		execve(exe, tree->args, get_env(shell->env));
	}
	g_sig = 1;
	waitpid(tree->pid, &(tree->status), 0);
	g_sig = 0;
	close(fd);
	return (1);
}

int			exec_cmd_write(int fd, char **args, char *path, t_shell *shell)
{
	int		pid;
	int		status;
	char	*exe;

	if (path == NULL || fd <= 0)
		return (0);
	if (ft_strncmp(path, args[0], ft_strlen(path)) != 0)
		exe = ft_strjoin(path, ft_strjoin("/", args[0]));
	else
		exe = args[0];
	if (args[0][0] != '.' && args[0][1] != '/')
		args[0] = ft_strjoin("./", args[0]);
	if ((pid = fork()) == 0)
	{
		if (dup2(fd, 1) == -1)
			return (0);
		execve(exe, args, get_env(shell->env));
	}
	g_sig = 1;
	waitpid(pid, &status, 0);
	g_sig = 0;
	close(fd);
	return (1);
}

int			exec_cmd_read(int fd, char **args, char *path, t_shell *shell)
{
	int		pid;
	int		status;
	char	*exe;

	if (path == NULL || fd <= 0)
		return (0);
	if (ft_strncmp(path, args[0], ft_strlen(path)) != 0)
		exe = ft_strjoin(path, ft_strjoin("/", args[0]));
	else
		exe = args[0];
	if (args[0][0] != '.' && args[0][1] != '/')
		args[0] = ft_strjoin("./", args[0]);
	if ((pid = fork()) == 0)
	{
		if (dup2(fd, 0) == -1)
			return (0);
		execve(exe, args, get_env(shell->env));
	}
	g_sig = 1;
	waitpid(pid, &status, 0);
	g_sig = 0;
	close(fd);
	return (1);
}
