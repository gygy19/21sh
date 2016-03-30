/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 07:28:40 by jguyet            #+#    #+#             */
/*   Updated: 2016/03/30 10:14:05 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*right;
	struct s_env	*left;
}					t_env;

typedef struct		s_st
{
	int				fd[2];
	int				fd2[2];
}					t_st;

typedef	struct		s_tree
{
	int				prio;
	int				ap;
	char			*cmd;
	char			**args;
	struct s_tree	*right;
	struct s_tree	*left;
	struct s_st		*st;
	int				status;
	int				pid;
	int				fd_in;
	int				fd_out;
	int				o_env;
}					t_tree;

typedef	struct		s_cmds
{
	int				id;
	char			*cmd;
	int				line;
	int				pointer;
	t_tree			*tree;
	int				wait;
	struct s_cmds	*up;
	struct s_cmds	*down;
	int				cp;
	char			*txt_cp;
	char			*key;
}					t_cmds;

typedef	struct		s_shell
{
	char			*get_pwd;
	char			*get_oldpwd;
	char			*get_home;
	t_env			*env;
	t_cmds			*cmds;
	struct termios	*tp;
	char			*path;
	char			*home;
	int				cat;
}					t_shell;

#endif
