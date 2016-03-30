/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 23:07:10 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/26 23:07:12 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "ft_cd.h"
#include "all.h"

void		process_tree(t_shell *shell, char **c)
{
	char	**args;
	t_tree	*tree;

	tree = NULL;
	if ((args = ft_strsplit(c[0], ' ')) && args[0])
	{
		if ((tree = prepar_tree(args, shell)))
		{
			if (!ft_cat(shell, tree))
			{
				tree->args = ft_strsplit(tree->cmd, ' ');
				if (tree->args[0] && !is_cmp1(tree, shell, 0)
					&& !is_cmp2(tree, shell) && !is_cmp3(tree, shell)
					&& !action(tree, shell))
					cmd_not_found(tree, shell);
			}
		}
		else
			invalid_cmd_notree(c[0]);
	}
	free(tree);
}

void		read_curent_shell(t_shell *shell)
{
	t_cmds	*cmds;
	char	**c;

	if ((cmds = get_cmd(&shell->cmds, shell)) && cmds->cmd && cmds->cmd[0])
	{
		remove_back_n(cmds);
		if (parse_error_minor(cmds) && parse_aggregation(cmds, 0))
		{
			c = ft_split_process(cmds->cmd, ';');
			while (c && c[0])
			{
				process_tree(shell, c);
				c++;
			}
		}
	}
	else if (cmds != NULL)
		clear_invalid_cmds(&cmds);
}

void		get_prompt(t_shell *shell)
{
	char	pwd[BUFF_SIZE + 1];

	getcwd(pwd, BUFF_SIZE);

	ft_putstr(START_PROMPT);
	g_prompt = ft_strlen(pwd) + ft_strlen("[] » ");
	if (ft_strncmp(pwd, shell->home, ft_strlen(shell->home)) == 0)
	{
		ft_putstr("~");
		g_prompt = ft_strlen("[~] » ");
		if (ft_strlen(shell->home) < ft_strlen(pwd))
		{
			ft_putstr(pwd + ft_strlen(shell->home));
			g_prompt = ft_strlen(pwd + ft_strlen(shell->home))
			+ ft_strlen("[~] » ");
		}
	}
	else
		ft_putstr(pwd);
	ft_putstr(END_PROMPT);
}

void		process_shell(t_shell *shell)
{
	while (1)
	{
		get_prompt(shell);
		read_curent_shell(shell);
	}
}
