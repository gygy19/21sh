/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_braces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 01:37:07 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/29 01:37:09 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"

static int	is_in(int in, int i, t_cmds *cmd)
{
	if ((cmd->cmd[(i > 1) ? i - 1 : 0] != '\\'
		&& cmd->cmd[i] == '\"')
		|| (cmd->cmd[(i > 1) ? i - 1 : 0] != '\\'
		&& cmd->cmd[i] == '(')
		|| (cmd->cmd[(i > 1) ? i - 1 : 0] != '\\'
		&& cmd->cmd[i] == '\'')
		|| (cmd->cmd[(i > 1) ? i - 1 : 0] != '\\'
		&& cmd->cmd[i] == '`'))
		in = cmd->cmd[i];
	return (in);
}

int			parse_braces(t_cmds *cmd, int in, int quotee, int quotef)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->cmd[i])
	{
		if (in && cmd->cmd[(i > 1) ? i - 1 : 0] != '\\' && cmd->cmd[i] == in)
			in = 0;
		else if (!in && is_in(in, i, cmd))
			in = cmd->cmd[i];
		if (!in && cmd->cmd[(i > 1) ? i - 1 : 0] != '\\' && cmd->cmd[i] == '{')
			quotee++;
		else if (!in && quotee % 2 && cmd->cmd[(i > 1) ? i - 1 : 0]
			!= '\\' && cmd->cmd[i] == '}')
			quotef++;
		i++;
	}
	if (quotee != quotef)
	{
		tmp = ft_strnew(1);
		tmp[0] = '\n';
		ft_strcat(cmd->cmd, tmp);
	}
	return (quotee - quotef);
}
