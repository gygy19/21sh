/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 13:56:51 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/24 13:56:52 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "all.h"
#include "libft.h"

#include <curses.h>
#include <term.h>

static int	quest_close(t_cmds **cmds, t_shell *shell)
{
	if (ft_strlen((*cmds)->cmd) == 0)
		exit(0);
	parse_key(185, cmds, shell);
	parse_key(DELETE, cmds, shell);
	return (1);
}

static int	parse_key_five(size_t key, t_cmds **cmd, t_shell *shell)
{
	if ((*cmd)->cp > -1)
	{
		(*cmd)->cp = -1;
		edit_cmd_cp(*cmd);
	}
	else if (key == 9)
		tab_search(cmd, shell);
	else if (key == 4)
		return (quest_close(cmd, shell));
	else if (key == 190 && (*cmd)->pointer > 0 && !(*cmd)->line)
	{
		move_cursor_left((*cmd)->pointer, (*cmd)->pointer);
		(*cmd)->pointer = 0;
	}
	else if (key == 188 && (*cmd)->pointer < (int)ft_strlen((*cmd)->cmd) && !(*cmd)->line)
	{
		move_cursor_right((*cmd)->pointer, ft_strlen((*cmd)->cmd) - (*cmd)->pointer);
		(*cmd)->pointer = ft_strlen((*cmd)->cmd);
	}
	else
		return (0);
	return (1);
}

static int	parse_key_four(int i, size_t key, t_cmds **cmd, t_shell *shell)
{
	if (key == 19)
	{
		if ((*cmd)->cp == -1)
		{
			(*cmd)->cp = 0;
			(*cmd)->txt_cp = ft_strnew(1);
			(*cmd)->txt_cp[0] = (*cmd)->cmd[(*cmd)->pointer];
		}
		else
		{
			(*cmd)->cp = -1;
			edit_cmd_cp(*cmd);
		}
	}
	else if (key == 24)
	{
		if (!(*cmd)->txt_cp && (*cmd)->up && (*cmd)->up->txt_cp)
			(*cmd)->txt_cp = (*cmd)->up->txt_cp;
		while ((*cmd)->txt_cp && (*cmd)->txt_cp[++i])
			process_key(*cmd, (*cmd)->txt_cp[i],\
			ft_strndup((*cmd)->txt_cp + i, 1), shell);
	}
	else
		return (parse_key_five(key, cmd, shell));
	return (1);
}

static int	parse_key_three(size_t key, t_cmds **cmd, t_shell *shell)
{
	if (key == 344)
	{
		while ((*cmd)->pointer > 0 && (*cmd)->cmd[(*cmd)->pointer] == ' ')
			parse_key(186, cmd, shell);
		while ((*cmd)->pointer > 0 && (*cmd)->cmd[(*cmd)->pointer] != ' ')
			parse_key(186, cmd, shell);
	}
	else if (key == 343)
	{
		while ((*cmd)->pointer < (int)ft_strlen((*cmd)->cmd)
			&& (*cmd)->cmd[(*cmd)->pointer] != ' ')
			parse_key(185, cmd, shell);
		while ((*cmd)->pointer < (int)ft_strlen((*cmd)->cmd)
			&& (*cmd)->cmd[(*cmd)->pointer] == ' ')
			parse_key(185, cmd, shell);
	}
	else
		return (parse_key_four(-1, key, cmd, shell));
	return (1);
}

int			parse_key_two(size_t key, t_cmds **cmd, t_shell *shell)
{
	//char	*tmp;

	if (key == 12)
	{
		ft_putstr(CLEAR_MINISHELL);
		get_prompt(shell);
		ft_putstr((*cmd)->cmd);
		return (1);
	}
	else if (key == BACK_N)
	{
		tputs(tgetstr("do", NULL), 1, tputs_putchar);
		ft_putstr(COLOR__RED);
		ft_putstr("\\ ");
		ft_putstr(COLOR__END);
		(*cmd)->line++;
		(*cmd)->pointer++;
	}
	else
		return (parse_key_three(key, cmd, shell));
	return (1);
}
