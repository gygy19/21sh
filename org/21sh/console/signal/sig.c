/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 22:11:20 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/26 22:11:22 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "all.h"
#include "sig.h"
#include "libft.h"

void	ctrlc(int i)
{
	t_shell *shell;
	t_cmds	*cmd;

	if (i == SIGINT && !g_sig)
	{
		shell = create_shell(NULL);
		cmd = shell->cmds;
		ft_putstr("\n");
		get_prompt(shell);
		while (cmd->down)
			cmd = cmd->down;
		cmd->cmd = ft_strnew(1);
		cmd->pointer = 0;
		cmd->key = NULL;
	}
	else
	{
		shell = create_shell(NULL);
		if (!shell->cat)
			return ;
		ft_putstr("^C");
		kill(shell->cat, SIGKILL);
	}
}

void	ctrlz(int i)
{
	if (i == SIGTSTP)
	{
	}
}

void	ctrlq(int i)
{
	if (i == SIGQUIT)
	{
	}
}
