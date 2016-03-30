/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 18:41:11 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/24 18:41:13 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "all.h"
#include "libft.h"

#include <curses.h>
#include <term.h>
#include <stdlib.h>

static void	verif_pos(t_cmds *cmd)
{
	if (cmd->pointer < (int)ft_strlen(cmd->cmd))
	{
		move_cursor_right(cmd->pointer, ft_strlen(cmd->cmd) - cmd->pointer);
		del_term_key(-1, ft_strlen(cmd->cmd) - cmd->pointer);
	}
}

int			up_history(t_cmds **cmd)
{
	t_cmds	*tmp;

	tmp = (*cmd)->up;
	if (tmp != NULL)
	{
		verif_pos(*cmd);
		while (tmp->up && tmp->id > ((*cmd)->wait - 1))
			tmp = tmp->up;
		if ((*cmd)->pointer > 0 && (*cmd)->wait == (*cmd)->id)
			while (tmp->up && ft_strncmp(tmp->cmd,
				(*cmd)->cmd, (*cmd)->pointer) != 0)
				tmp = tmp->up;
		if (!tmp)
			return (1);
		del_term_key(-1, (*cmd)->pointer);
		ft_strdel(&(*cmd)->cmd);
		(*cmd)->cmd = ft_strdup(tmp->cmd);
		(*cmd)->wait = tmp->id;
		ft_putstr((*cmd)->cmd);
		(*cmd)->pointer = ft_strlen(tmp->cmd);
	}
	return (1);
}

int			down_history(t_cmds **cmd)
{
	t_cmds	*tmp;

	tmp = (*cmd);
	if (tmp != NULL && tmp->wait != tmp->id)
	{
		verif_pos(*cmd);
		while (tmp->up && tmp->id != (*cmd)->wait)
			tmp = tmp->up;
		while (tmp->down && tmp->id < ((*cmd)->wait + 1))
			tmp = tmp->down;
		if (!tmp)
			return (1);
		del_term_key(-1, (*cmd)->pointer);
		ft_strdel(&(*cmd)->cmd);
		(*cmd)->cmd = tmp->cmd ? ft_strdup(tmp->cmd) : ft_strnew(1);
		(*cmd)->wait = tmp->id;
		ft_putstr((*cmd)->cmd);
		(*cmd)->pointer = ft_strlen(tmp->cmd);
	}
	return (1);
}
