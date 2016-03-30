/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 07:19:25 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/03 07:19:27 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CD_H
# define FT_CD_H

# include "struct.h"

# ifdef IS_CD

#  include <stdlib.h>
#  include <unistd.h>
#  include <sys/stat.h>
#  include <dirent.h>

#  include "libft.h"
#  include "ft_cd.h"

char		*get_arg(char *args);
size_t		have_right_open(char *dir);
size_t		is_dir(t_shell *shell, char *dir, char *cd, int put);
size_t		is_local(char *pwd);
void		print_error_malloc(char *txt);
char		*mod_point(char *args);
char		*del_arg(char *args, size_t len);

# endif

void		put_over_args(void);
void		ft_cd(char *args, t_shell *shell);
void		ft_cd_two(char *args1, char *args2, t_shell *shell, char *tmp);

#endif
