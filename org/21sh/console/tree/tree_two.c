/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 05:01:48 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/10 05:01:50 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "all.h"
#include "libft.h"

t_tree		*get_end_tree(t_tree *tree)
{
	t_tree *tmp;

	tmp = tree;
	if (tmp == NULL)
		return (NULL);
	while (tmp->right != NULL)
		tmp = tmp->right;
	return (tmp);
}

int			is_autorised(char *txt)
{
	int prio;

	prio = txt[1] ? (txt[0] + txt[1]) : txt[0];
	if (prio == '|'
		|| prio == '>'
		|| prio == '<'
		|| prio == ('<' + '<')
		|| prio == ('>' + '<'))
		return (0);
	return (1);
}

void		add_while_card(t_tree **tree, char *dir, t_shell *shell)
{
	DIR				*dirp;
	struct dirent	*files;

	if (dir[0] == '\0')
		dir = ft_strdup(shell->get_pwd);
	if (is_directory(dir))
	{
		files = malloc(sizeof(struct dirent));
		dirp = open_directory(dir);
		get_end_tree(*tree)->cmd = ft_strjoin(get_end_tree(*tree)->cmd, " ");
		while ((files = readdir(dirp)) != 0)
		{
			if (files->d_name[0] == '.')
				continue ;
			if (ft_strcmp(shell->get_pwd, dir) != 0)
				get_end_tree(*tree)->cmd = ft_strjoin(\
					get_end_tree(*tree)->cmd, dir);
			get_end_tree(*tree)->cmd = ft_strjoin(ft_strjoin(\
				get_end_tree(*tree)->cmd, files->d_name), " ");
		}
		get_end_tree(*tree)->cmd[ft_strlen(\
		get_end_tree(*tree)->cmd) - 1] = '\0';
	}
}

int			verif_min_tree(char ***tmp, t_tree **tree, int i)
{
	char	**cmd;

	cmd = *tmp;
	if (ft_strcmp(cmd[i], "ls") == 0)
		(*tmp)[i] = ft_strdup("ls -G");
	if ((cmd[i][ft_strlen(cmd[i]) - 1] != '*'
		&& part_tree(i, tree, cmd))
		|| (cmd[i][ft_strlen(cmd[i]) - 1] != '*'
		&& part_two_tree(i, tree, cmd))
		|| (cmd[i][ft_strlen(cmd[i]) - 1] != '*'
		&& part_tree_tree(i, tree, cmd)))
		return (1);
	return (0);
}

int			prepar_tree_suite(char ***tmp, t_tree **tree, t_shell *shell, int i)
{
	char	**cmd;

	cmd = *tmp;
	if (get_end_tree(*tree) && cmd[i][ft_strlen(cmd[i]) - 1] == '*')
	{
		add_while_card(tree, ft_strndup(cmd[i], ft_strlen(cmd[i]) - 1), shell);
		(*tmp)[i] = "";
		return (1);
	}
	else if (get_end_tree(*tree) != NULL && get_end_tree(*tree)->prio == '.')
		get_end_tree(*tree)->cmd = ft_strjoin(ft_strjoin(\
		get_end_tree(*tree)->cmd, " "), cmd[i]);
	else
		create_tree(cmd[i], tree, ".", 0);
	return (0);
}
