/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 03:13:27 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/14 03:13:29 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>

#include "all.h"
#include "libft.h"

void		one_file(int nbr, char *save, t_shell *shell, t_cmds **cmd)
{
	while (save[nbr])
	{
		process_key(*cmd, save[nbr], ft_strndup(save + nbr, 1), shell);
		nbr++;
	}
	if (nbr && is_directory(get_dir((*cmd)->cmd, ' ')))
		process_key(*cmd, '/', ft_strdup("/"), shell);
}

void		multiple_file_c(int nbr, char **tb, t_shell *shell, t_cmds **cmd)
{
	int o;
	int h;
	int i;

	o = 1;
	h = 0;
	while (o)
	{
		i = 0;
		while (tb[i] && o)
		{
			if (i != 0 && tb[i][nbr] != h)
				o = 0;
			else
				h = tb[i][nbr];
			i++;
		}
		if (o)
		{
			process_key(*cmd, h, ft_strndup(tb[0] + nbr, 1), shell);
			nbr++;
		}
	}
	if (nbr && is_directory(get_dir((*cmd)->cmd, ' ')))
		process_key(*cmd, '/', ft_strdup("/"), shell);
}

void		search_file(char *dir, char *s, t_cmds **cmd, t_shell *shell)
{
	DIR				*dirp;
	struct dirent	*files;
	char			*save;
	int				nbr;
	char			*suite;

	nbr = 0;
	suite = ft_strnew(1);
	files = malloc(sizeof(struct dirent));
	dirp = open_directory(dir);
	while ((files = readdir(dirp)) != 0)
	{
		if (files->d_name[0] == '.')
			continue ;
		if (ft_strncmp(s, files->d_name, ft_strlen(s)) == 0)
		{
			save = ft_strdup(files->d_name);
			nbr++;
			suite = ft_strjoin(ft_strjoin(suite, " "), save);
		}
	}
	if (nbr == 1)
		one_file(ft_strlen(s), save, shell, cmd);
	else if (nbr > 1 && nbr <= 1000)
		multiple_file_c(ft_strlen(s), ft_strsplit(suite, ' '), shell, cmd);
}

void		tab_search(t_cmds **cmd, t_shell *shell)
{
	char	*dir;
	char	*direction;

	dir = get_dir(ft_strndup((*cmd)->cmd, (*cmd)->pointer), ' ');
	if (dir[0] == '\0')
		return ;
	if (dir[ft_strlen(dir) - 1] == '*')
	{
		//dir[ft_strlen(dir) - 1] = '\0';
		//add_stars(cmd, dir, shell);
		return ;
	}
	direction = get_dir(dir, '/');
	if (direction[0] == '\0'
		|| (ft_strlen(dir) == ft_strlen(direction) && direction[0] != '/'))
		direction = ft_strdup(shell->get_pwd);
	else
	{
		dir = ft_strndup(dir, ft_strlen(dir) - (ft_strlen(direction) - 1));
	}
	if (ft_strcmp(direction, shell->get_pwd) == 0 && is_directory(direction))
		search_file(direction, dir, cmd, shell);
	else if (is_directory(dir))
		search_file(dir, direction + 1, cmd, shell);
}
