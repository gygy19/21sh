/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_aggregation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 06:49:24 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/14 06:49:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"

static int	is_in(int in, int i, t_cmds *cmd)
{
	if ((cmd->cmd[(i > 1) ? i - 1 : 0] != '\\'
		&& cmd->cmd[i] == '\"')
		|| (cmd->cmd[(i > 1) ? i - 1 : 0] != '\\'
		&& cmd->cmd[i] == '{')
		|| (cmd->cmd[(i > 1) ? i - 1 : 0] != '\\'
		&& cmd->cmd[i] == '(')
		|| (cmd->cmd[(i > 1) ? i - 1 : 0] != '\\'
		&& cmd->cmd[i] == '\'')
		|| (cmd->cmd[(i > 1) ? i - 1 : 0] != '\\'
		&& cmd->cmd[i] == '`'))
		in = cmd->cmd[i];
	return (in);
}

static int	is_not_good_fd(char *cmd, int i)
{
	int		max;
	int		fd;
	char	*tmp;

	max = i;
	while ((i && cmd[i] <= '9' && cmd[i] >= '0')
		|| (cmd[i] && cmd[i] == '-'))
		i--;
	tmp = ft_strndup(cmd + i, max - (i - 1));
	fd = ft_atoi(tmp);
	if (fd > 9 || fd < 0 || i == max)
	{
		if (i == max)
		{
			while (i && cmd[i] != ' ')
				i--;
			tmp = ft_strndup(cmd + i + 1, max - i);
			ft_putstr_fd(tmp, 2);
		}
		else
			ft_putnbr_fd(fd, 2);
		ft_putstr_fd(": Bad file descriptor\n", 2);
		return (0);
	}
	return (1);
}

static int	is_not_good_fd2(char *cmd, int i)
{
	int	min;
	int	fd;

	min = i;
	while ((cmd[i] && cmd[i] <= '9' && cmd[i] >= '0')
		|| (cmd[i] && cmd[i] == '-'))
		i++;
	fd = ft_atoi(ft_strndup(cmd + min, i));
	if (fd > 3 || fd < 0)
	{
		ft_putnbr_fd(fd, 2);
		ft_putstr_fd(": Bad file descriptor\n", 2);
		return (0);
	}
	return (1);
}

int			parse_aggregation(t_cmds *cmd, int in)
{
	int		i;
	int		error;

	i = 0;
	error = 1;
	while (cmd->cmd[i])
	{
		if (in && cmd->cmd[(i > 1) ? i - 1 : 0] != '\\' && cmd->cmd[i] == in)
			in = 0;
		else if (!in && is_in(in, i, cmd))
			in = cmd->cmd[i];
		if ((!in && cmd->cmd[(i > 1) ? i - 1 : 0] != '\\' && cmd->cmd[i] == '>'
			&& cmd->cmd[i + 1] && cmd->cmd[i + 1] == '&'))
		{
			if (cmd->cmd[i + 2] && cmd->cmd[i + 2] == '-')
				error = is_not_good_fd(cmd->cmd, i - 1);
			if (error)
				error = is_not_good_fd2(cmd->cmd, i + 2);
		}
		i++;
	}
	return (error);
}
