/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 22:39:09 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/03 01:38:46 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "libft.h"
#include "all.h"

char		*get_name(char *args)
{
	int i;

	i = 0;
	while (args[i] && args[i] != ' ')
		i++;
	return (ft_strndup(args, i));
}

char		*get_args(char *txt)
{
	int i;

	i = 0;
	while (txt[i] && txt[i] != '\n' && txt[0] != ' ')
		i++;
	return (ft_strtrim(ft_strdup(txt + 1)));
}

void		ft_error(char *str)
{
	ft_putstr(str);
	exit(-1);
}

t_shell		*create_shell(char **env)
{
	static t_shell	*shell;
	char			buff[BUFF_SIZE + 1];

	if (shell)
		return (shell);
	shell = NULL;
	if (!(shell = (struct s_shell*)malloc(sizeof(struct s_shell))))
		print_error_malloc("[create_shell] t_shell");
	getcwd(buff, BUFF_SIZE);
	shell->get_pwd = ft_strdup(buff);
	shell->get_home = getenv("HOME") ?\
	ft_strdup(getenv("HOME")) : ft_strdup("/");
	if (!is_directory(shell->get_home))
		shell->get_home = ft_strdup("/");
	shell->get_oldpwd = ft_strdup("/");
	shell->env = NULL;
	if (env[0])
		shell->env = create_total_env(NULL, env);
	shell->cmds = NULL;
	return (shell);
}
