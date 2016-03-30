/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 22:53:15 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/02 23:12:51 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "all.h"

void			print_error_malloc(char *txt)
{
	ft_putstr_fd("Error Malloc in ", 2);
	ft_putstr_fd(txt, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

void			ft_error_malloc(char *str)
{
	ft_putstr("Error malloc in ");
	ft_putstr(str);
	exit(-1);
}

void			print_back_n(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			ft_putstr_fd("\\n", 2);
		else
			ft_putchar_fd(str[i], 2);
		i++;
	}
}

void			invalid_cmd_notree(char *txt)
{
	ft_putstr("21sh: command not found: ");
	print_back_n(txt);
	ft_putstr("\n");
}

void			cmd_not_found(t_tree *tree, t_shell *shell)
{
	char	pwd[BUFF_SIZE + 1];

	getcwd(pwd, BUFF_SIZE);
	if (!is_exe2(ft_strjoin(pwd, "/"), tree->args[0], shell))
		return ;
	if (tree->args[0] && tree->args[0][0] && tree->args[0][1]
		&& tree->args[0][0] != '.' && tree->args[0][1] != '/')
		ft_putstr("21sh: command not found: ");
	else
		ft_putstr("21sh: no such file or directory: ");
	print_back_n(tree->cmd);
	ft_putstr("\n");
}

void			file_not_found(char *cmd)
{
	ft_putstr("21sh: no such file or directory: ");
	ft_putstr(cmd);
	ft_putstr("\n");
}
