/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 13:39:37 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/24 13:39:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>

#include "libft.h"
#include "all.h"

char		**get_path(t_env *env)
{
	t_shell	*shell;

	(void)env;
	shell = create_shell(NULL);
	return (ft_strsplit(shell->path, ':'));
}

char	*get_path_rescure(char *cmd)
{
	int len;

	len = ft_strlen(cmd) - 1;
	while (len > 0)
	{
		if (cmd[len] == '/')
			return (ft_strndup(cmd, len));
		len--;
	}
	return (cmd);
}

char		*get_path_by_cmd(char *cmd, char **path, char *local)
{
	DIR				*dirp;
	int				i;
	struct dirent	*files;

	i = 0;
	if (!(files = malloc(sizeof(struct dirent))))
		print_error_malloc("[get_path_by_cmd] struct dirent");
	while (path && path[i] && cmd[0] != '.' && cmd[1] != '/')
	{
		if (path[i][0] == '\0')
			path[i] = ft_strdup("/bin");
		if ((dirp = open_directory(path[i])) == NULL)
			return (NULL);
		while ((files = readdir(dirp)) != 0)
			if (ft_strcmp(files->d_name, have_path(path[i], cmd)) == 0
				&& is_exe(path[i], files->d_name))
				return (path[i]);
		i++;
	}
	if ((cmd[0] == '.' && cmd[1] == '/' && (dirp = open_directory(local))))
	while ((files = readdir(dirp)) != 0)
		if (ft_strcmp(files->d_name, cmd + 2) == 0
			&& is_exe(local, files->d_name))
			return (local);
	if ((dirp = open_directory(get_path_rescure(cmd))))
		while ((files = readdir(dirp)) != 0)
			if (ft_strcmp(files->d_name, cmd + (ft_strlen(get_path_rescure(cmd)) + 1)) == 0
				&& is_exe(get_path_rescure(cmd), files->d_name))
				return (get_path_rescure(cmd));
	return (NULL);
}
