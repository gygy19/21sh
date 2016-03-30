/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 21:25:19 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/28 21:25:20 by jguyet           ###   ########.fr       */
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

int			verif_key(char *str, int i, char *key)
{
	while (str[i])
	{
		if (ft_strncmp(str + i, key, ft_strlen(key)) == 0 && str[i - 1] && str[i - 1] == ' ')
			return (0);
		i++;
	}
	return (1);
}

char		*get_end_string(char *cmd)
{
	int i;

	i = ft_strlen(cmd);
	while (i > 0)
	{
		if (cmd[i] == '\n')
			return (cmd + i + 1);
		i--;
	}
	i = ft_strlen(cmd);
	while (i > 0)
	{
		if (cmd[i] == ' ')
			return (cmd + i + 1);
		i--;
	}
	return (NULL);
}

int			parse_dirdir(t_cmds *cmd, int in)
{
	int		i;
	int		ok;

	ok = 0;
	i = 0;
	while (cmd->cmd[i])
	{
		if (in && cmd->cmd[(i > 1) ? i - 1 : 0] != '\\' && cmd->cmd[i] == in)
			in = 0;
		else if (!in && is_in(in, i, cmd))
			in = cmd->cmd[i];
		if (!in && cmd->cmd[i] == '<' && cmd->cmd[i + 1] && cmd->cmd[i + 1] == '<')
		{
			ok = 1;
			break ;
		}
		i++;
	}
	if (ok && cmd->key != NULL)
	{
		if (ft_strcmp(get_end_string(cmd->cmd), cmd->key) == 0)
			return (0);
		cmd->cmd = ft_strjoin(cmd->cmd, " \n");
		return (1);
	}
	else if (ok)
	{
		cmd->key = ok ? ft_strdup(get_end_string(cmd->cmd)) : NULL;
		cmd->cmd = ft_strjoin(cmd->cmd, " \n");
	}
	return (ok ? 1 : 0);
}
