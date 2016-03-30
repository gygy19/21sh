/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 23:30:19 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/26 23:30:21 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "all.h"
#include "libft.h"

#include <curses.h>
#include <term.h>

size_t		read_key(void)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	int		i;
	size_t	key;

	key = 0;
	i = 0;
	while ((ret = read(0, buf, BUFF_SIZE)) == 0)
		buf[ret] = '\0';
	buf[ret] = '\0';
	while (i < ret)
	{
		key += buf[i];
		i++;
	}
	return (key);
}

void		process_key(t_cmds *cmd, size_t key, char *tmp, t_shell *shell)
{
	if (parse_key(key, &cmd, shell))
		return ;
	if (cmd->line && (get_length__b(cmd->cmd, ft_strlen(cmd->cmd)) + 1) >= (int)(get_size_x() / 2))
			return ;
	if (cmd->pointer < (int)ft_strlen(cmd->cmd) && ft_isprint(key))
	{
		edit_cmd(ft_strdup(tmp), cmd);
	}
	else if (ft_isprint(key))
	{
		ft_putchar(key);
		cmd->wait = cmd->id;
		cmd->pointer++;
		ft_strncat(cmd->cmd, ft_strdup(tmp), 1);
	}
}

int			check_doublon(t_cmds **cmd, size_t key)
{
	if (key != BACK_N)
		return (1);
	if (!parse_simple_quote(*cmd, 0) && !parse_back(*cmd)
		&& !parse_double_quote(*cmd, 0) && !parse_braces(*cmd, 0, 0, 0)
		&& !parse_back_quote(*cmd, 0) && !parse_dirdir(*cmd, 0))
		return (0);
	if ((*cmd)->pointer && (*cmd)->pointer < (int)ft_strlen((*cmd)->cmd))
	{
		move_cursor_right((*cmd)->pointer, ft_strlen((*cmd)->cmd) - (*cmd)->pointer);
		(*cmd)->pointer = ft_strlen((*cmd)->cmd);
	}
	return (1);
}

t_cmds		*get_cmd(t_cmds **cmds, t_shell *shell)
{
	size_t	key;
	t_cmds	*new;
	char	*tmp;

	tmp = ft_strnew(2);
	if ((*cmds) == NULL)
		new = create_cmds(&(*cmds), NULL);
	else
	{
		new = (*cmds);
		while (new->down != NULL)
			new = new->down;
		new = create_cmds(&new->down, new);
	}
	new->line = 0;
	while (((key = read_key()) != BACK_N) || check_doublon(&new, key))
		process_key(new, (tmp[0] = key) ? key : key, tmp, shell);
	new->wait = new->id;
	if (new->pointer < (int)ft_strlen(new->cmd))
		move_cursor_right(new->pointer, ft_strlen(new->cmd) - new->pointer);
	new->pointer = 0;
	new->key = NULL;
	ft_putchar('\n');
	ft_strdel(&tmp);
	return (new);
}
