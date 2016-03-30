/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 07:14:24 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/03 07:14:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define IS_CD

#include "ft_cd.h"
#include "all.h"

char		*get_arg(char *args)
{
	size_t i;

	i = 0;
	while (args[i] && args[i] != '/')
		i++;
	return (ft_strndup(args, i));
}

void		put_error_cd(char *error_type, char *dir, char *cd, char *home)
{
	ft_putstr_fd(error_type, 2);
	if (ft_strncmp(dir, home, ft_strlen(dir) - ft_strlen(cd)) == 0)
	{
		if (dir[ft_strlen(dir)] == '/')
			dir[ft_strlen(dir)] = '\0';
		ft_putstr_fd(dir, 2);
	}
	else
		ft_putstr_fd(cd, 2);
	ft_putstr_fd("\n", 2);
}

size_t		have_right_open(char *dir)
{
	DIR *dirp;

	dirp = NULL;
	dirp = opendir(dir);
	if (dirp == NULL)
		return (0);
	closedir(dirp);
	return (1);
}

size_t		is_dir(t_shell *sh, char *dir, char *cd, int put)
{
	size_t		ret;
	struct stat	*stats;

	if (dir[0] == '\0')
		return (1);
	ret = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[exist_file] struct stat");
	if (stat(dir, stats) == 0)
		if (S_ISDIR(stats->st_mode))
			ret = 1;
	free(stats);
	if (ret == 1)
	{
		if (!have_right_open(dir))
		{
			if (put)
				put_error_cd("cd: permission denied: ", dir, cd, sh->get_home);
			ret = 0;
		}
	}
	else if (put)
		put_error_cd("cd: no such file or directory: ", dir, cd, sh->get_home);
	return (ret);
}
