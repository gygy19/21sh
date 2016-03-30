/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_caractere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 03:37:06 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/27 03:37:08 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "all.h"

#include <curses.h>
#include <term.h>

void		del_term_key(int pointer, int nbr)
{
	if (nbr)
	{
		if (pointer > -1)
			move_cursor_left(pointer, 1);
		else
			tputs(tgetstr("le", NULL), 1, tputs_putchar);
		tputs(tgetstr("cd", NULL), 1, tputs_putchar);
	}
	if ((nbr - 1) > 0)
		del_term_key(pointer - 1, nbr - 1);
}

int			remove_key(t_cmds **cmd)
{
	(*cmd)->wait = (*cmd)->id;
	if (!(*cmd)->pointer)
		return (1);
	del_term_key(1, 1);
	(*cmd)->cmd[ft_strlen((*cmd)->cmd) - 1] = '\0';
	(*cmd)->pointer--;
	return (1);
}

static int	print_next_cursor(t_cmds *cmd, char *tmp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!tmp)
	{
		cmd->pointer = ft_strlen(cmd->cmd);
		return (0);
	}
	while (tmp[i])
	{
		if (((cmd->pointer + len + g_prompt) / get_size_x())
			< ((cmd->pointer + len + (g_prompt + 1)) / get_size_x()))
		{
			if (!cmd->line)
				tputs(tgetstr("do", NULL), 1, tputs_putchar);
		}
		ft_putchar(tmp[i]);
		len++;
		i++;
	}
	return (len);
}

void		remove_back_n(t_cmds *cmd)
{
	int		stop;
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	stop = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i - 1] && !stop && cmd->cmd[i - 1]
			== '\\' && cmd->cmd[i] == '\n')
		{
			tmp = ft_strdup(cmd->cmd + (i + 1));
			tmp2 = ft_strndup(cmd->cmd, i - 1);
			ft_strdel(&cmd->cmd);
			cmd->cmd = ft_strjoin(tmp2, tmp);
			stop = 1;
			i -= 1;
			continue ;
		}
		stop = 0;
		i++;
	}
}

int			remove_key_line(t_cmds *cmd)
{
	char	*tmp;
	char	*tmp2;
	char	*new;
	int		len;

	if (cmd->line)
		return (1);
	if (cmd->cmd[cmd->pointer])
		tmp = ft_strdup(cmd->cmd + cmd->pointer);
	else
		tmp = NULL;
	tmp2 = ft_strndup(cmd->cmd, cmd->pointer - 1);
	len = ft_strlen(tmp);
	new = tmp2;
	cmd->cmd = ft_strjoin(new, tmp);
	move_cursor_right(cmd->pointer, len);
	del_term_key(cmd->pointer + len, len + 1);
	cmd->pointer--;
	len = print_next_cursor(cmd, tmp);
	while (len--)
		move_cursor_left(cmd->pointer + len + 1, 1);
	return (1);
}
