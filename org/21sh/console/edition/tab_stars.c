/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_stars.c                                        :+:      :+:    :+:   */
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

char		*get_dir(char *txt, char key)
{
	int len;

	len = ft_strlen(txt);
	while (len && txt[len] != key)
		len--;
	return (ft_strtrim(txt + len));
}

char		**get_in_dir(char *dir, t_shell *shell)
{
	char			**tmp;
	int				i;
	DIR				*dirp;
	struct dirent	*files;

	i = 0;
	tmp = NULL;
	if (!(tmp = (char **)malloc(sizeof(char *) * (1025))))
		print_error_malloc("[get_in_dir] char **");
	files = (struct dirent*)malloc(sizeof(struct dirent));
	dirp = open_directory(dir);
	while ((files = readdir(dirp)) != 0)
	{
		if (files->d_name[0] == '.')
			continue ;
		if (ft_strcmp(shell->get_pwd, dir) != 0)
			tmp[i] = ft_strjoin(dir, files->d_name);
		else
			tmp[i] = ft_strdup(files->d_name);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void		add_stars(t_cmds **cmd, char *dir, t_shell *shell)
{
	int				i;
	int				len;
	char			**tmp;
	char			*tm;

	if (dir[0] == '\0')
		dir = ft_strdup(shell->get_pwd);
	if (!is_directory(dir))
		return ;
	process_key(*cmd, DELETE, "del", shell);
	if (!(i = 0) && ft_strcmp(shell->get_pwd, dir) != 0)
		while (dir[i++])
			process_key(*cmd, DELETE, "del", shell);
	tmp = get_in_dir(dir, shell);
	i = -1;
	while (tmp[++i])
	{
		len = 0;
		while (tmp[i][len] && ft_isprint(tmp[i][len]) && (tm = ft_strnew(2)))
		{
			tm[0] = tmp[i][len];
			process_key(*cmd, tmp[i][len++], tm, shell);
		}
		process_key(*cmd, ' ', " ", shell);
	}
}
