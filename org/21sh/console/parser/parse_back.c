/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 22:16:40 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/28 22:16:42 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"

int			parse_back(t_cmds *cmd)
{
	size_t	len;
	int		quote;

	len = ft_strlen(cmd->cmd);
	quote = 0;
	if (len == 1 && cmd->cmd[0] == '\\')
		quote++;
	else
		while (len > 0 && cmd->cmd[len - 1] == '\\')
		{
			quote++;
			len--;
		}
	return (quote % 2);
}
