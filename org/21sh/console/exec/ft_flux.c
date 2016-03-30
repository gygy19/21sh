/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_default.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 03:29:37 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/10 03:29:38 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "all.h"

void		redir_flux(t_tree *tree)
{
	if (tree->ap == 100)
	{
		g_fd_flux = dup(tree->fd_in);
		if (tree->fd_out == '-')
			close(tree->fd_in);
		else
			dup2(g_fd_flux, tree->fd_out);
	}
}

void		final_redir_flux(t_tree *tree)
{
	if (tree->ap == 100)
	{
		if (tree->fd_out != '-')
			dup2(g_fd_flux, tree->fd_out);
	}
}
