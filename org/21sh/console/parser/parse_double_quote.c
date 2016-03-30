/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 22:16:07 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/28 22:16:08 by jguyet           ###   ########.fr       */
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

int			parse_double_quote(t_cmds *cmd, int in)
{
	int		i;
	int		quote;
	char	*tmp;

	i = 0;
	quote = 0;
	while (cmd->cmd[i])
	{
		if (in && cmd->cmd[(i > 1) ? i - 1 : 0] != '\\' && cmd->cmd[i] == in)
			in = 0;
		else if (!in && is_in(in, i, cmd))
			in = cmd->cmd[i];
		if ((!in && cmd->cmd[(i > 1) ? i - 1 : 0] != '\\'
			&& cmd->cmd[i] == '\"')
			|| (in == '\"' && cmd->cmd[i] == '\"'))
			quote++;
		i++;
	}
	if (quote % 2)
	{
		tmp = ft_strnew(1);
		tmp[0] = '\n';
		ft_strcat(cmd->cmd, tmp);
	}
	return (quote % 2);
}
