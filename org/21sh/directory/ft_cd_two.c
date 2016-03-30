/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 01:37:35 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/06 01:37:41 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define IS_CD

#include "ft_cd.h"

size_t		is_local(char *pwd)
{
	if (ft_strlen(pwd) == 1 && pwd[0] == '.')
		return (1);
	return (0);
}

char		*mod_point(char *args)
{
	size_t	p;
	size_t	i;
	char	*new;

	i = 0;
	p = 0;
	new = ft_strnew(1);
	while (args[i] && args[i] == '.')
	{
		i++;
		p++;
	}
	if (p == ft_strlen(args))
	{
		p /= 2;
		while (p)
		{
			new = ft_strjoin(new, "../");
			p--;
		}
		return (new);
	}
	return (args);
}

void		put_over_args(void)
{
	ft_putstr_fd("ft_cd: too many arguments", 2);
}

void		ft_cd_two(char *args1, char *args2, t_shell *shell, char *tmp)
{
	int		arg_len;
	char	*arg;
	char	*end;

	end = NULL;
	if (!tmp || tmp[0] == '\0')
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putstr_fd(args1, 2);
		return ;
	}
	arg = get_arg(tmp);
	arg_len = ft_strlen(arg);
	if (ft_strcmp(arg, args1) == 0)
	{
		end = ft_strndup(shell->get_pwd,
			ft_strlen(shell->get_pwd) - ft_strlen(tmp));
		end = ft_strjoin(end, args2);
		end = ft_strjoin(end, tmp + ft_strlen(args1));
		ft_cd(end, shell);
		return ;
	}
	ft_cd_two(args1, args2, shell, del_arg(tmp, arg_len));
}
