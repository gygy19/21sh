/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 22:56:57 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/26 22:56:59 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "ft_cd.h"
#include "all.h"

void		put_history(t_cmds *cmd)
{
	while (cmd)
	{
		ft_putstr(" ");
		ft_putnbr(cmd->id);
		ft_putstr("  ");
		ft_putstr(cmd->cmd);
		ft_putstr("\n");
		cmd = cmd->down;
	}
}

int			is_cmp1(t_tree *tree, t_shell *shell, int i)
{
	if (ft_strcmp(tree->args[0], "exit") == 0)
		exit(tree->args[1] ? ft_atoi(tree->args[1]) : 0);
	else if (ft_strcmp(tree->args[0], "cd") == 0)
	{
		(void)i;
		while (tree->args[i])
			i++;
		if (i > 3)
			put_over_args();
		else if (i == 3)
			ft_cd_two(tree->args[1], tree->args[2], shell, shell->get_pwd);
		else if (tree->args[1])
			ft_cd(tree->args[1], shell);
		else
			ft_cd("~", shell);
		return (1);
	}
	else if ((ft_strcmp(tree->args[0], "clear") == 0)
		|| (ft_strcmp(tree->args[0], "HOME") == 0))
	{
		ft_strcmp(tree->args[0], "clear") == 0 ?\
		ft_putstr(CLEAR_MINISHELL) : ft_cd("~", shell);
		return (1);
	}
	return (0);
}

int			is_cmp2(t_tree *tree, t_shell *shell)
{
	if (ft_strcmp(tree->args[0], "setenv") == 0)
	{
		if (tree->args[1] != NULL || tree->args[2] != NULL
			|| tree->args[3] == NULL)
			set_env(shell->env, tree->args[1], tree->args[2], shell);
		else
			ft_putstr_fd("21sh : two arguments for setenv\n", 2);
		return (1);
	}
	else if (ft_strcmp(tree->args[0], "unsetenv") == 0)
	{
		if (tree->args[1] == NULL || tree->args[2] != NULL)
		{
			ft_putstr_fd("21sh : one argument for setenv\n", 2);
			return (1);
		}
		tree->args[1] != NULL ? unset_env(shell->env, tree->args[1]) : 0;
		return (1);
	}
	else if (ft_strcmp(tree->args[0], "history") == 0)
	{
		put_history(shell->cmds);
		return (1);
	}
	return (0);
}

int			is_cmp3(t_tree *tree, t_shell *shell)
{
	if (ft_strcmp(tree->args[0], "whoami") == 0)
	{
		print_user(shell->env);
		return (1);
	}
	else if (ft_strcmp(tree->args[0], "pwd") == 0)
	{
		ft_putstr(shell->get_pwd);
		ft_putstr("\n");
		return (1);
	}
	else if (ft_strcmp(tree->args[0], "env") == 0)
	{
		if (tree->args[1] && ft_strcmp(tree->args[1], "-i") == 0)
		{
			if (tree->args[2])
			{
				tree->args = tree->args + 2;
				tree->o_env = 0;
				return (0);
			}
		}
		else
			print_env(shell->env, shell);
		return (1);
	}
	return (0);
}

int			action(t_tree *tree, t_shell *shell)
{
	if (tree->cmd[0])
		return (exec_search(tree, shell));
	return (0);
}
