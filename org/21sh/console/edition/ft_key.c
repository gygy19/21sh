/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 13:56:51 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/24 13:56:52 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "libft.h"

void		ft_key_left(t_cmds **cmd)
{
	if ((*cmd)->pointer)
	{
		if ((*cmd)->line && get_length__b((*cmd)->cmd, (*cmd)->pointer) == 2)
			return ;
		if ((*cmd)->cp > -1)
		{
			(*cmd)->cp--;
			edit_cmd_cp(*cmd);
			(*cmd)->txt_cp[ft_strlen((*cmd)->txt_cp) - 1] = '\0';
		}
		if ((*cmd)->cmd[(*cmd)->pointer - 1]
			&& (*cmd)->cmd[(*cmd)->pointer - 1] == '\n')
			return ;
		move_cursor_left(1, 1);
		(*cmd)->pointer--;
	}
}

void		ft_key_right(t_cmds **cmd)
{
	int pt;

	if ((*cmd)->pointer < (int)ft_strlen((*cmd)->cmd))
	{
		pt = get_length__b((*cmd)->cmd, (*cmd)->pointer);
		if ((*cmd)->line == 0)
			move_cursor_right((*cmd)->pointer, 1);
		else
			move_cursor_right(1, 1);
		(*cmd)->pointer++;
		if ((*cmd)->cp > -1)
		{
			edit_cmd_cp(*cmd);
			(*cmd)->cp++;
			(*cmd)->txt_cp = ft_strjoin((*cmd)->txt_cp,\
			ft_strndup((*cmd)->cmd + (*cmd)->pointer, 1));
		}
	}
}
