/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 01:24:27 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/02 01:24:29 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "all.h"
#include "libft.h"

void		create_tree(char *cmd, t_tree **tree, char *priority, int ap)
{
	t_tree *new;

	new = NULL;
	if ((*tree) != NULL)
		new = get_end_tree((*tree))->right;
	if (!(new = (t_tree *)malloc(sizeof(t_tree))))
		ft_error_malloc("[create_tree] t_tree");
	new->cmd = cmd;
	new->left = get_end_tree((*tree));
	new->right = NULL;
	if (new->left != NULL)
		get_end_tree((*tree))->right = new;
	new->prio = priority[1] ? (priority[0] + priority[1]) : priority[0];
	new->ap = ap;
	new->o_env = 1;
	new->args = NULL;
	if ((*tree) == NULL)
		*tree = new;
}

int			part_tree(int i, t_tree **tree, char **cmd)
{
	int ret;

	ret = 0;
	if (cmd[i + 1] != NULL && ft_strlen(cmd[i + 1]) == 1
		&& ft_strcmp(cmd[i + 1], "|") == 0 && get_end_tree(*tree) != NULL
		&& get_end_tree(*tree)->prio == '.' && (ret = 1))
	{
		get_end_tree(*tree)->cmd = ft_strjoin(ft_strjoin(\
		get_end_tree(*tree)->cmd, " "), cmd[i]);
		get_end_tree(*tree)->prio = '|';
	}
	else if (cmd[i + 1] != NULL && ft_strlen(cmd[i + 1]) == 1
		&& ft_strcmp(cmd[i + 1], "|") == 0 && (ret = 1))
		create_tree(cmd[i], tree, "|", 1);
	else if (cmd[i + 1] != NULL && ft_strlen(cmd[i + 1]) == 2
		&& ft_strcmp(cmd[i + 1], ">>") == 0 && get_end_tree(*tree) != NULL
		&& get_end_tree(*tree)->prio == '.' && (ret = 1))
	{
		get_end_tree(*tree)->cmd = ft_strjoin(ft_strjoin(\
			get_end_tree(*tree)->cmd, " "), cmd[i]);
		get_end_tree(*tree)->prio = '>' + '<';
	}
	return (ret);
}

int			part_two_tree(int i, t_tree **tree, char **cmd)
{
	int ret;

	ret = 0;
	if (cmd[i + 1] != NULL && ft_strlen(cmd[i + 1]) == 2
		&& ft_strcmp(cmd[i + 1], ">>") == 0 && (ret = 1))
	{
		create_tree(cmd[i], tree, "><", 1);
	}
	else if (cmd[i + 1] != NULL && cmd[i + 2] != NULL
		&& ft_strlen(cmd[i + 1]) == 1
		&& ft_strcmp(cmd[i + 1], "<") == 0 && get_end_tree(*tree) != NULL
		&& get_end_tree(*tree)->prio == '.' && (ret = 1))
	{
		get_end_tree(*tree)->cmd = ft_strjoin(ft_strjoin(\
		get_end_tree(*tree)->cmd, " "), cmd[i]);
		get_end_tree(*tree)->prio = '<';
	}
	else if (cmd[i + 1] != NULL && cmd[i + 2] != NULL
		&& ft_strlen(cmd[i + 1]) == 1
		&& ft_strcmp(cmd[i + 1], "<") == 0 && (ret = 1))
		create_tree(cmd[i], tree, "<", 1);
	return (ret);
}

int			part_tree_tree(int i, t_tree **tree, char **cmd)
{
	int ret;

	ret = 0;
	if (cmd[i + 1] != NULL && ft_strlen(cmd[i + 1]) == 1
		&& ft_strcmp(cmd[i + 1], ">") == 0 && get_end_tree(*tree) != NULL
		&& get_end_tree(*tree)->prio == '.' && (ret = 1))
	{
		get_end_tree(*tree)->cmd = ft_strjoin(ft_strjoin(\
		get_end_tree(*tree)->cmd, " "), cmd[i]);
		get_end_tree(*tree)->prio = '>';
	}
	else if (cmd[i + 1] != NULL && ft_strlen(cmd[i + 1]) == 1
		&& ft_strcmp(cmd[i + 1], ">") == 0 && (ret = 1))
		create_tree(cmd[i], tree, ">", 1);
	return (ret);
}

char		*get_end_dirdir(char **cmd, int i)
{
	char	*key;
	char	*result;

	if (!cmd[i])
		return (NULL);
	key = cmd[i];
	result = NULL;
	i++;
	while (cmd[i] && ft_strcmp(cmd[i], key))
	{
		if (result == NULL)
			result = ft_strdup(cmd[i]);
		else
			result = ft_strjoin(result, cmd[i]);
		i++;
	}
	return (result);
}

t_tree		*prepar_tree(char **cmd, t_shell *shell)
{
	int		i;
	t_tree	*tree;

	i = 0;
	if (!(tree = NULL) && cmd[0] == NULL)
		return (NULL);
	while (cmd[i] != NULL)
	{
		if (cmd[i + 1] != NULL && ft_strlen(cmd[i + 1]) == 2
			&& ft_strcmp(cmd[i + 1], "<<") == 0)
		{
			create_tree("echo", &tree, "|", 1);
			get_end_tree(tree)->cmd = ft_strjoin(ft_strjoin(\
			get_end_tree(tree)->cmd, " "), get_end_dirdir(cmd, i + 2));
			create_tree(cmd[i], &tree, ".", 1);
			while (cmd[i + 1] && ft_strcmp(cmd[i + 1], "|") && ft_strcmp(cmd[i + 1], "<") && ft_strcmp(cmd[i + 1], ">>") && ft_strcmp(cmd[i + 1], ">"))
				i++;
			i++;
			if (cmd[i])
				get_end_tree(tree)->prio = cmd[i][0];
		}
		else if (verif_min_tree(&cmd, &tree, i))
		{
		}
		else if (is_autorised(cmd[i]))
			if (prepar_tree_suite(&cmd, &tree, shell, i))
				continue ;
		if (cmd[i + 1] != NULL && ft_strlen(cmd[i + 1]) > 2
		&& is_close_fd(cmd[i + 1])
		&& get_prio_close_fd(cmd[i + 1], &tree, cmd, i))
			cmd[i + 1] = "";
		i++;
	}
	return (tree);
}
