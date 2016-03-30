/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 22:38:56 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/02 23:11:49 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "all.h"
#include "libft.h"
#include "sig.h"
#include "ft_cd.h"

void	create_env_global(t_shell *shell)
{
	char	buff[BUFF_SIZE + 1];

	getcwd(buff, BUFF_SIZE);
	if (!shell->env)
		shell->env = create_env(NULL, "PWD", buff);
	if (!get_env_value(shell->env, "PWD"))
		set_env(shell->env, "PWD", ft_strdup(buff), shell);
	if (!get_env_value(shell->env, "HOME"))
		set_env(shell->env, "HOME", ft_strdup("/"), shell);
	if (!get_env_value(shell->env, "USER"))
		set_env(shell->env, "USER", "?", shell);
	if (!get_env_value(shell->env, "SHLVL"))
		set_env(shell->env, "SHLVL", "1", shell);
	if (!get_env_value(shell->env, "OLDPWD"))
		set_env(shell->env, "OLDPWD", ft_strdup("/"), shell);
	if (!get_env_value(shell->env, "PATH")
		|| ft_strcmp(get_env_value(shell->env, "PATH"),\
		"/usr/bin:/bin:/usr/sbin:/sbin"))
		set_env(shell->env, "PATH", "/usr/bin:/bin:/usr/sbin:/sbin", shell);
}

int		main(int argc, char **argv, char **env)
{
	t_shell			*shell;
	struct termios	*tp;

	(void)argc;
	(void)argv;
	if (!(tp = (struct termios *)malloc(sizeof(struct termios))))
		ft_error_malloc("[main] struct termios");
	load_console(tp);
	g_sig = 0;
	signal(SIGINT, ctrlc);
	signal(SIGTSTP, ctrlz);
	signal(SIGQUIT, ctrlq);
	shell = create_shell(env);
	shell->tp = tp;
	create_env_global(shell);
	shell->path = ft_strdup(get_env_value(shell->env, "PATH"));
	shell->home = ft_strdup(get_env_value(shell->env, "HOME"));
	shell->cat = 0;
	process_shell(shell);
	return (0);
}
