/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 03:29:02 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/10 03:29:04 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "ft_cd.h"
#include "all.h"
#include "sig.h"

static int	sub_pipe_first(t_tree *tree)
{
	char	buff[4097];
	int		ret;

	ret = read(tree->left->st->fd[0], buff, 4096);
	close(tree->left->st->fd[0]);
	close(tree->left->st->fd[1]);
	if (pipe(tree->st->fd) == -1)
		return (0);
	if (pipe(tree->st->fd2) == -1)
		return (0);
	redir_flux(tree);
	write(tree->st->fd[1], buff + 1, ret - 1);
	final_redir_flux(tree);
	close(tree->st->fd[1]);
	return (1);
}

static int	sub_pipe_second(t_tree *tree)
{
	char	buff[4097];
	int		ret;

	ret = read(tree->st->fd2[0], buff, 4096);
	close(tree->st->fd2[0]);
	close(tree->st->fd2[1]);
	if (pipe(tree->st->fd) == -1)
		return (0);
	redir_flux(tree);
	write(tree->st->fd[1], buff, ret);
	final_redir_flux(tree);
	close(tree->st->fd[1]);
	return (1);
}

int			exec_pipe_suite(t_tree *tree, char *path, t_shell *shell)
{
	char	*exe;

	if (!(exe = get_exename(tree, path, shell)))
		return (0);
	tree->args[0] = modif_dir(tree);
	tree->st = create_st();
	if (sub_pipe_first(tree) == 0)
		return (0);
	if ((tree->pid = fork()) == 0)
	{
		if (dup2(tree->st->fd[0], 0) == -1)
			return (0);
		if (dup2(tree->st->fd2[1], 1) == -1)
			return (0);
		ft_putstr(" ");
		execve(exe, tree->args, get_env(shell->env));
	}
	g_sig = 1;
	if (waitpid(tree->pid, &(tree->status), 0) == -1)
		return (0);
	g_sig = 0;
	if (sub_pipe_second(tree) == 0)
		return (0);
	return (1);
}

int			exec_start_pipe(t_tree *tree, char *path, t_shell *shell)
{
	char	*exe;

	if (!(exe = get_exename(tree, path, shell)))
		return (0);
	tree->args[0] = modif_dir(tree);
	tree->st = create_st();
	pipe(tree->st->fd);
	if ((tree->pid = fork()) == 0)
	{
		redir_flux(tree);
		close(tree->st->fd[0]);
		if (dup2(tree->st->fd[1], 1) == -1)
			return (0);
		ft_putstr(" ");
		execve(exe, tree->args, get_env(shell->env));
		final_redir_flux(tree);
	}
	g_sig = 1;
	if (waitpid(tree->pid, &(tree->status), 0) == -1)
		return (0);
	g_sig = 0;
	return (1);
}

int			exec_cmd_final_pipe(t_tree *tree, char *path, t_shell *shell)
{
	char	*exe;

	if (!(exe = get_exename(tree, path, shell)))
		return (0);
	tree->args[0] = modif_dir(tree);
	tree->st = create_st();
	if (!tree->left->left || tree->left->left->prio != '|')
		if (sub_pipe_write(tree, 1) == 0)
			return (0);
	if ((tree->pid = fork()) == 0)
	{
		if (dup2(tree->left->st->fd[0], 0) == -1)
			return (0);
		redir_flux(tree);
		execve(exe, tree->args, get_env(shell->env));
		final_redir_flux(tree);
	}
	g_sig = 1;
	if (waitpid(tree->pid, &(tree->status), 0) == -1)
		return (0);
	g_sig = 0;
	return (1);
}
