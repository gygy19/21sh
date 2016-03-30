/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition.c                                          :+:      :+:    :+:   */
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

t_cmds		*create_cmds(t_cmds **cmd, t_cmds *up)
{
	if ((up && !up->cmd) || (up && (up->up != NULL
		&& ft_strcmp(up->cmd, up->up->cmd) == 0)))
	{
		up->cmd ? ft_strdel(&up->cmd) : 0;
		up->cmd = ft_strnew(1);
		up->wait = up->id;
		return (up);
	}
	if (!((*cmd) = (t_cmds*)malloc(sizeof(t_cmds))))
		return (NULL);
	if (up != NULL)
	{
		(*cmd)->up = up;
		up->down = (*cmd);
	}
	else
		(*cmd)->up = NULL;
	(*cmd)->id = up ? up->id + 1 : 0;
	(*cmd)->cmd = ft_strnew(1);
	(*cmd)->pointer = 0;
	(*cmd)->wait = (*cmd)->id;
	(*cmd)->tree = NULL;
	(*cmd)->down = NULL;
	(*cmd)->cp = -1;
	return (*cmd);
}

int			get_length__b(char *cmd, int pointer)
{
	int len;
	int tmp;

	len = 0;
	tmp = pointer;
	while (tmp)
	{
		if (cmd[tmp] == '\n')
			return (len);
		len++;
		tmp--;
	}
	return (pointer);
}

int			parse_key(size_t key, t_cmds **cmd, t_shell *shell)
{
	if (key == DELETE && (*cmd)->pointer == (int)ft_strlen((*cmd)->cmd))
	{
		 if ((*cmd)->line && get_length__b((*cmd)->cmd, (*cmd)->pointer) == 2)
		 	return (0);
			return (remove_key(cmd));
	}
	else if (!(*cmd)->line && key == DELETE && (*cmd)->pointer
		&& get_length__b((*cmd)->cmd, (*cmd)->pointer) != 0)
		return (remove_key_line((*cmd)));
	else if (key == 183 || key == 297)
		return (up_history(cmd));
	else if (key == 184 || key == 298)
		return (down_history(cmd));
	else if (key == 186)
	{
		ft_key_left(cmd);
		return (1);
	}
	else if (key == 185)
	{
		ft_key_right(cmd);
		return (1);
	}
	return (parse_key_two(key, cmd, shell));
}
