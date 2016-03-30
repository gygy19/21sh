/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 23:21:30 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/15 23:21:32 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "libft.h"

int			is_close_fd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '>')
		i++;
	if (!cmd[i] || (cmd[i + 1] && cmd[i + 1] != '&'))
		return (0);
	return (1);
}

int			get_first_fd(char *cmd, int i)
{
	int n;
	int ret;

	n = 0;
	if (i == 1)
	{
		ret = 1;
		i = 0;
	}
	while (cmd[i] && cmd[i] != '>')
	{
		if (cmd[i] < '0' || cmd[i] > '9')
			n++;
		i++;
	}
	if (ret)
		return (n);
	return (i);
}

void		end_prio_close_fd(char *cmd, t_tree **tree, int i, int n)
{
	while (cmd[i] != '&')
	{
		if (cmd[i] < '0' || cmd[i] > '9')
			n++;
		i--;
	}
	if (n == 1 || (n == 2 && cmd[i + 1]
		&& cmd[i + 1] == '-' && cmd[i + 2] == '\0'))
		get_end_tree(*tree)->fd_out = cmd[i + 1]\
		== '-' ? '-' : (cmd[ft_strlen(cmd) - 1] - 48);
	else
	{
		get_end_tree(*tree)->prio = '>';
		get_end_tree(*tree)->ap = 1;
		create_tree(cmd + (i + 1), tree, ".", 0);
	}
}

int			get_prio_close_fd(char *cmd, t_tree **tree, char **cmd_base, int ii)
{
	int n;
	int	i;

	n = get_first_fd(cmd, 1);
	i = get_first_fd(cmd, 0);
	if (!cmd[i] || (cmd[i + 1] && cmd[i + 2] && cmd[i + 2] != '&'))
		return (0);
	if (!*tree)
		create_tree(cmd_base[ii], tree, ".", 100);
	if (n == 0)
	{
		get_end_tree(*tree)->ap = 100;
		get_end_tree(*tree)->fd_in = (cmd[0] - 48);
	}
	else
	{
		get_end_tree(*tree)->prio = '.';
		get_end_tree(*tree)->ap = 1;
		(*tree)->cmd = ft_strjoin(ft_strjoin((*tree)->cmd, " ")\
			, ft_strndup(cmd, i + 2));
		return (1);
	}
	end_prio_close_fd(cmd, tree, ft_strlen(cmd), 0);
	return (1);
}
