/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 22:42:32 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/26 22:42:34 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termios.h>
#include <curses.h>

#include "all.h"
#include "libft.h"
#include "sig.h"

#include <term.h>

int		load_console(struct termios *term)
{
	char	*ent;

	ent = NULL;
	ent = ft_strdup("xterm-256color");
	if (tgetent(NULL, ent) != 1)
		ft_error("[modif_term] Unknow TERM variable\n");
	if (tcgetattr(0, term) == -1)
		ft_error("[modif_term] Failed request tcgetattr!\n");
	term->c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (0);
	return (1);
}

char		*read_keyi(void)
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
	return (ft_strdup(buf));
}

void	process_cat(t_shell *shell, char *n, char *tmp)
{
	n = ft_strnew(2);
	while (shell->cat)
	{
		tmp = ft_strnew(1);
		while (shell->cat && (n = read_keyi())[0] != '\n')
		{
			tmp = ft_strjoin(tmp, n);
			ft_putstr(n);
		}
		if (tmp[0] == '\0')
			ft_putstr("\n\n");
		else
			ft_putstr("\n");
		ft_putstr(tmp);
		ft_putstr("\n");
	}
}

int		ft_cat(t_shell *shell, t_tree *tree)
{
	if (ft_strcmp(tree->cmd, "cat") != 0)
		return (0);
	shell->cat = 1;
	if ((tree->pid = fork()) == 0)
		process_cat(shell, NULL, NULL);
	g_sig = 1;
	shell->cat = tree->pid;
	waitpid(tree->pid, &(tree->status), 0);
	g_sig = 0;
	shell->cat = 0;
	return (1);
}
