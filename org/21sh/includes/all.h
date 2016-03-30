/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 22:57:20 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/02 23:09:40 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <dirent.h>
# include <termios.h>
# include <unistd.h>

# include "struct.h"
# define CLEAR_MINISHELL "\033[2J\033[H"
# define BUFF_SIZE 1024
# define BACK_N 10
# define DELETE 127

# define COLOR__RED "\e[31m"
# define COLOR__END "\e[00m"
# define COLOR__CPY "\e[41m"
# define START_PROMPT "[\e[95m"
# define END_PROMPT "\e[00m] » "

t_cmds		*get_cmd(t_cmds **cmds, t_shell *shell);
char		*get_name(char *args);
char		*get_v(char *env, int start);
char		*get_args(char *txt);
int			is_directory(char *file);
void		cmd_not_found(t_tree *tree, t_shell *shell);
t_shell		*create_shell(char **env);
void		process_shell(t_shell *shell);
t_env		*get_end_env(t_env *env);
int			unload_console(struct termios *term);
void		print_error_malloc(char *txt);
void		add_pwd(char *args, t_shell *shell);
void		print_env(t_env *env, t_shell *shell);
void		unset_env(t_env *env, char *name);
char		*get_env_value(t_env *env, char *key);
t_env		*create_total_env(t_env *env, char **c_env);
void		set_env(t_env *env, char *name, char *value, t_shell *shell);
char		*verif_env(char *name, char *value, t_shell *shell);
t_env		*create_env(t_env *left, char *name, char *value);
char		*get_path_by_cmd(char *cmd, char **path, char *local);
int			default_exec(t_tree *tree, char *path, t_shell *shell);
char		**get_path(t_env *env);
DIR			*open_directory(char *dir);
int			is_exe2(char *dir, char *file, t_shell *shell);
int			is_exe(char *dir, char *file);
void		print_user(t_env *env);
char		*have_path(char *path, char *cmd);
char		**get_env(t_env *env);
char		**get_path(t_env *env);
char		*get_path_by_cmd(char *cmd, char **path, char *local);
int			tputs_putchar(int c);
void		del_term_key(int pointer, int nbr);
int			remove_key(t_cmds **cmd);
int			up_history(t_cmds **cmd);
int			down_history(t_cmds **cmd);
void		put_history(t_cmds *cmd);
size_t		get_size_x(void);
void		move_cursor_right(int pointer, int nbr);
void		move_cursor_left(int pointer, int nbr);
int			load_console(struct termios *term);
void		ft_error_malloc(char *str);
void		ft_error(char *str);
void		edit_cmd(char *key, t_cmds *cmd);
void		ft_key_left(t_cmds **cmd);
void		ft_key_right(t_cmds **cmd);
int			parse_key(size_t key, t_cmds **cmd, t_shell *shell);
int			parse_key_two(size_t key, t_cmds **cmd, t_shell *shell);
t_cmds		*create_cmds(t_cmds	**cmd, t_cmds *up);
int			remove_key_line(t_cmds *cmd);
void		process_key(t_cmds *cmd, size_t key, char *tmp, t_shell *shell);
int			parse_simple_quote(t_cmds *cmd, int in);
int			parse_double_quote(t_cmds *cmd, int in);
int			parse_back(t_cmds *cmd);
int			parse_braces(t_cmds *cmd, int in, int quotee, int quotef);
int			parse_error_minor(t_cmds *cmd);
int			parse_back_quote(t_cmds *cmd, int in);
void		remove_back_n(t_cmds *cmd);
int			parse_aggregation(t_cmds *cmd, int in);
char		**ft_split_process(char const *s, char c);
t_tree		*prepar_tree(char **cmd, t_shell *shell);
int			is_cmp1(t_tree *tree, t_shell *shell, int i);
int			is_cmp2(t_tree *tree, t_shell *shell);
int			is_cmp3(t_tree *tree, t_shell *shell);
int			action(t_tree *tree, t_shell *shell);
int			exec_cmd_write(int fd, char **args, char *path, t_shell *shell);
int			exec_cmd_read(int fd, char **args, char *path, t_shell *shell);
int			exec_dir_enter(t_tree *tree, t_shell *shell);
int			cmd_sh(char **args, t_shell *shell);
int			exec_cmd_pipe(t_st *st, t_tree *tree, char *path, t_shell *shell);
int			exec_cmd_write_end_pipe(int fd, t_tree *tree, char *path,
			t_shell *shell);
int			exec_cmd_write_end_dir(int fd, t_tree *tree);
int			exec_start_pipe(t_tree *tree, char *path, t_shell *shell);
int			exec_pipe_suite(t_tree *tree, char *path, t_shell *shell);
int			exec_cmd_final_pipe(t_tree *tree, char *path, t_shell *shell);
char		*get_exename(t_tree *tree, char *path, t_shell *shell);
int			is_close_fd(char *cmd);
void		create_tree(char *cmd, t_tree **tree, char *priority, int ap);
int			part_tree(int i, t_tree **tree, char **cmd);
int			part_two_tree(int i, t_tree **tree, char **cmd);
int			part_tree_tree(int i, t_tree **tree, char **cmd);
int			get_prio_close_fd(char *cmd, t_tree **tree,
			char **cmd_base, int ii);
int			verif_min_tree(char ***tmp, t_tree **tree, int i);
int			prepar_tree_suite(char ***tmp, t_tree **tree,
			t_shell *shell, int i);
char		*modif_dir(t_tree *tree);
void		invalid_cmd_notree(char *txt);
void		clear_invalid_cmds(t_cmds **cmds);
int			get_fd_by_dir(t_tree *tree);
t_st		*create_st(void);
int			sub_pipe_write(t_tree *tree, int ant);
int			exec_search(t_tree *tree, t_shell *shell);
void		file_not_found(char *cmd);
t_tree		*get_end_tree(t_tree *tree);
int			is_autorised(char *txt);
void		edit_cmd_cp(t_cmds *cmd);
void		tab_search(t_cmds **cmd, t_shell *shell);
int			start_ft_select(int argc, char **argv);
void		get_prompt(t_shell *shell);
char		*get_dir(char *txt, char key);
void		add_while_card(t_tree **tree, char *dir, t_shell *shell);
void		add_stars(t_cmds **cmd, char *dir, t_shell *shell);
void		final_redir_flux(t_tree *tree);
void		redir_flux(t_tree *tree);
int			get_length__b(char *cmd, int pointer);
int			parse_dirdir(t_cmds *cmd, int in);
int			ft_cat(t_shell *shell, t_tree *tree);
int			g_fd_flux;
int			g_prompt;
#endif
