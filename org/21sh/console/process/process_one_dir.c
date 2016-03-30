/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_one_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 23:52:51 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/02 23:52:53 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "struct.h"
#include "libft.h"

int			get_fd_by_dir(t_tree *tree)
{
	int fd;

	fd = 0;
	if (tree->prio == ('>' + '<') && tree->right)
		fd = open(tree->right->cmd, O_WRONLY | O_CREAT
			| O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (tree->prio == ('>') && tree->right)
		fd = open(tree->right->cmd, O_WRONLY | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (tree->prio == ('<') && tree->right)
		fd = open(tree->right->cmd, O_RDWR);
	return (fd);
}

char		*have_path(char *path, char *cmd)
{
	if (ft_strncmp(path, cmd, ft_strlen(path)) == 0)
		return (cmd + ft_strlen(path) + 1);
	return (cmd);
}

void		clear_invalid_cmds(t_cmds **cmds)
{
	if ((*cmds)->up)
		(*cmds)->up->down = NULL;
	(*cmds) = NULL;
}
