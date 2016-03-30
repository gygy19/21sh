/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 03:36:21 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/27 03:36:22 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "all.h"

#include <curses.h>
#include <term.h>

void		move_cursor_left(int pointer, int nbr)
{
	int line;
	int i;

	line = (pointer + g_prompt) / get_size_x();
	while (nbr)
	{
		if (((pointer + (g_prompt - 1)) / get_size_x())
			< ((pointer + g_prompt) / get_size_x()))
		{
			i = line == 0 ? get_size_x() - g_prompt : get_size_x();
			tputs(tgetstr("up", NULL), 1, tputs_putchar);
			while (i--)
				tputs(tgetstr("nd", NULL), 1, tputs_putchar);
			line--;
		}
		else
			tputs(tgetstr("le", NULL), 1, tputs_putchar);
		pointer--;
		nbr--;
	}
}

void		move_cursor_right(int pointer, int nbr)
{
	while (nbr)
	{
		if (((pointer + g_prompt) / get_size_x())
			< ((pointer + g_prompt + 1) / get_size_x()))
		{
			tputs(tgetstr("do", NULL), 1, tputs_putchar);
		}
		else
			tputs(tgetstr("nd", NULL), 1, tputs_putchar);
		pointer++;
		nbr--;
	}
}
