/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_default.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 03:29:37 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/10 03:29:38 by jguyet           ###   ########.fr       */
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

static void		exec_search_pipe(char *path, t_tree *tree, t_shell *shell)
{
	if ((tree->left && tree->left->prio == '|' && !tree->right)
		|| (tree->left && tree->left->prio == '|'
		&& tree->right && tree->right->prio != '|'))
	{
		if (!exec_pipe_suite(tree, path, shell))
			cmd_not_found(tree, shell);
	}
	else if (tree->right && tree->right->prio == '|')
	{
		if (tree->left && tree->left->prio == '|')
		{
			if (!exec_pipe_suite(tree, path, shell))
				cmd_not_found(tree, shell);
		}
		else if (!exec_start_pipe(tree, path, shell))
			cmd_not_found(tree, shell);
	}
	else if (!exec_start_pipe(tree, path, shell))
		cmd_not_found(tree, shell);
}

static t_tree	*exec_search_dir(char *path, t_tree *tree, t_shell *shell)
{
	t_tree	*tmp;

	if ((tree->left && tree->left->prio == '|' && !tree->left->left)
		|| (tree->left && tree->left->prio == '|' && tree->left->left
		&& tree->left->left->prio == '|'))
	{
		exec_cmd_write_end_pipe(get_fd_by_dir(tree), tree, path, shell);
		if (tree->right && tree->right->prio == '|')
			return (tree->right);
	}
	else
	{
		tmp = tree;
		while ((tree && tree->prio == '>')
			|| (tree && tree->prio == ('>' + '<')))
		{
			exec_cmd_write(get_fd_by_dir(tree), tmp->args, path, shell);
			tree = tree->right;
		}
	}
	if (tree && tree->right && tree->right->prio == '.')
		tree = tree->right;
	return (tree);
}

static t_tree	*exec_search_end_dir(char *path, t_tree *tree, t_shell *shell)
{
	t_tree	*tmp;

	tmp = tree;
	while (tree && tree->prio == '<')
	{
		if (!exec_cmd_read(get_fd_by_dir(tree), tmp->args, path, shell))
			file_not_found(tree->right->cmd);
		tree = tree->right;
	}
	return (tree);
}

int				exec_search(t_tree *tree, t_shell *shell)
{
	char	*path;

	if (!tree)
		return (1);
	if (!tree->args)
		tree->args = ft_strsplit(tree->cmd, ' ');
	path = get_path_by_cmd(tree->args[0], get_path(shell->env), shell->get_pwd);
	if (tree->prio == '|')
		exec_search_pipe(path, tree, shell);
	else if ((tree->prio == '>') || (tree->prio == ('>' + '<')))
		tree = exec_search_dir(path, tree, shell);
	else if (tree->prio == '<')
		tree = exec_search_end_dir(path, tree, shell);
	else if ((tree->left && tree->left->prio == '|' && !tree->left->left)
		|| (tree->left && tree->left->prio == '|'
		&& tree->left->left && tree->left->left->prio == '|'))
	{
		if (!exec_cmd_final_pipe(tree, path, shell))
			cmd_not_found(tree, shell);
	}
	else if (!default_exec(tree, path, shell))
		cmd_not_found(tree, shell);
	return (exec_search(tree ? tree->right : tree, shell));
}

int				default_exec(t_tree *tree, char *path, t_shell *shell)
{
	char	*exe;

	if (path == NULL || !(exe = get_exename(tree, path, shell)))
		return (0);
	if (tree->args[0][0] != '.' && tree->args[0][1] != '/')
		tree->args[0] = ft_strjoin("./", tree->args[0]);
	if ((tree->pid = fork()) == 0)
	{
		redir_flux(tree);
		execve(exe, tree->args, tree->o_env ? get_env(shell->env) : NULL);
		final_redir_flux(tree);
	}
	g_sig = 1;
	waitpid(tree->pid, &(tree->status), 0);
	g_sig = 0;
	return (1);
}
