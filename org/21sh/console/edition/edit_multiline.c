/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_multiline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 03:36:45 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/27 03:36:46 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "all.h"

#include <curses.h>
#include <term.h>

static int	print_next_cursor(t_cmds *cmd, char *tmp, int ok)
{
	int	i;
	int	len;
	int	pt;

	i = 0;
	len = 0;
	pt = cmd->pointer;
	while (tmp[i])
	{
		if (ok && ((pt + len + g_prompt) / get_size_x())
			< ((pt + len + g_prompt + 1) / get_size_x()))
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

void		reset_cmd_cp(t_cmds *cmd)
{
	int len;

	len = ft_strlen(cmd->cmd) - cmd->pointer;
	if (len < 0)
		len = 0;
	move_cursor_right(cmd->pointer, len);
	del_term_key(cmd->pointer + len, ft_strlen(cmd->cmd));
	print_next_cursor(cmd, cmd->cmd, 0);
	while (len--)
		move_cursor_left(cmd->pointer + len, 1);
}

void		edit_cmd_cp(t_cmds *cmd)
{
	int		len;
	char	*tmp;

	len = ft_strlen(cmd->cmd) - cmd->pointer;
	if (len < 0)
		len = 0;
	if (cmd->cp == -1)
	{
		reset_cmd_cp(cmd);
		return ;
	}
	move_cursor_right(cmd->pointer, len);
	del_term_key(cmd->pointer + len, len + (cmd->cp + 1));
	ft_putstr(COLOR__CPY);
	tmp = ft_strndup(cmd->cmd + (cmd->pointer - (cmd->cp + 1)), (cmd->cp + 1));
	cmd->pointer -= (cmd->cp + 1);
	print_next_cursor(cmd, tmp, 0);
	cmd->pointer += (cmd->cp + 1);
	ft_putstr(COLOR__END);
	len = print_next_cursor(cmd, cmd->cmd + cmd->pointer, 0);
	while (len--)
		move_cursor_left(cmd->pointer + len, 1);
}

void		edit_cmd(char *key, t_cmds *cmd)
{
	char	*tmp;
	char	*tmp2;
	char	*new;
	int		len;

	if (cmd->cmd[cmd->pointer])
		tmp = ft_strdup(cmd->cmd + cmd->pointer);
	else
		tmp = NULL;
	tmp2 = ft_strndup(cmd->cmd, cmd->pointer);
	len = ft_strlen(tmp);
	//ft_strdel(&cmd->cmd);
	new = ft_strjoin(tmp2, key);
	cmd->cmd = ft_strjoin(new, tmp);
	move_cursor_right(cmd->pointer, len);
	del_term_key(cmd->pointer + len, len);
	ft_putchar(key[0]);
	cmd->pointer++;
	len = print_next_cursor(cmd, tmp, 1);
	//ft_strdel(&tmp);
	//ft_strdel(&tmp2);
	while (len--)
		move_cursor_left(cmd->pointer + len + 1, 1);
}
