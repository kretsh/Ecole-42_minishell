/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:57:00 by cowen             #+#    #+#             */
/*   Updated: 2021/12/23 16:55:09 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# define EXIT_NO_ERROR 0
# define PREV 1
# define CURR 2
# define EXIT_WITH_ERROR_1 1
# define SUCCESS 0
# define FAIL -1
# define PIPE_ERROR -1
# define CHILD 0
# define NO 0
# define YES 1
# define GET_PATH_CURRENT_DIR 1
# define WRITE_PATH_CURRENT_DIR 0
# define PROG_NAME	"\001\x1b[34m\002minishell\001\x1b[0m\002$ "
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <limits.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>

typedef struct s_data
{
	t_cmd	*cmd_start;
	t_cmd	*envp_list;
	int		parse_error;
	int		return_value;
	char	*path_to_cmd;
	char	*line_from_read;
	char	*line_from_read_before_trim;
	char	**paths_to_binary;
	char	**envp;
	int		justlvl;
}			t_data;

char	**path_parser_from_envp(t_cmd *list);
void	free_envp(t_data *data);
int		my_echo(char **argv);
int		my_cd(char **argv, t_cmd *envp_list);
char	*home_dir(t_cmd *envp_list);
void	make_envp(t_data *data, char **envp);
void	print_env(t_cmd *list);
int		envp_from_list_to_array(t_data *data);
void	del_from_env(char **argv, t_cmd *list, t_data *data);
void	export_to_env(char **argv, t_cmd **list, t_data *data);
void	signal_catcher(void);
void	signal_handler(int SIGNUM);
int		check_argv_for_existing(char *argv, t_cmd **list);
void	parse_double_quotes(t_data *data);
char	**list_to_str_arr(t_cmd **start);
void	parse_quotes(t_data *data, char *str, t_cmd **cmd);
void	get_cmd_and_argv_from_line(t_data *data, t_cmd **line);
void	get_cmd_and_argv_from_list(t_data *data);
t_cmd	*ft_lstnew_char(char c);
char	*search_env(char *env, t_data *data);
void	search_wild_cards(t_cmd **start);
int		run_commands(t_data *data, t_cmd *cmd_start);
int		check_builtins(t_cmd *cmd_start, t_data *data);
int		parse_line(t_data *data, t_cmd *cmd_start);
int		run_flags_cmd(t_data *data, t_cmd *cmd_start);
int		heredoc_checker(t_data *data, t_cmd **cmd_start);
void	heredoc_doing(t_data *data);
void	prin_lists_of_cmd(t_cmd *buf);
void	exit_with_exit(t_data *data, char **argv);
int		check_valid_export(char *argv, int flag);
void	free_cmd(t_data *data);
void	free_line(t_cmd *line);
void	free_envp_list(t_cmd *envp_list);
char	**free_string_array(char **str);
int		check_builtins_here(t_cmd *cmd_start);
void	exit_write(int i, t_data *data);
int		check_minus(char minus);
void	export_no_arguments(t_cmd **list);
int		write_export_error(t_data *data, char *argv);
int		export_with_arguments(char *argv, t_cmd **list, t_data *data);
int		check_argv_for_existing_without_equal(char *argv, t_cmd **list);
int		check_d_quotes(t_cmd *new_list, char *str);
int		check_quotes(t_cmd *new_list, char *str);
int		check_space(t_cmd *new_list);
void	flag_initilization(t_cmd *list, int flag, int or, int and);
void	null_static_values(t_cmd *list, int *cmd, int *or, int *and);
void	check_next_symbol(char *str, int *cmd);
void	and_oder_or_checking(int flag, int *and, int *or);
void	error_on_parsing_flag(t_cmd *list, char *str);
void	pipe_checking(t_cmd *list, char *str, int *cmd);
void	null_pipes(int *pipe_in, int *pipe_out);
void	check_parenthesis(t_cmd *lst, char *str);
int		check_cmd_num(t_cmd *list, char *str);
void	check_argv(t_cmd *new_list);
void	check_pipe(t_cmd *lst, char *str);
void	check_wild_card(t_cmd *list);
void	parenthesis_remove_flag(t_cmd *lst, int *parenthesis, int flag);
void	sub_minishell(t_data *data, char **argv);
void	init_redir_r(t_cmd *lst, int redirect_right, int redirect_d_right);
void	null_redir_r(t_cmd *lst, int *redirect_right,
			int *redirect_d_right, int flag);
void	search_for_double_redirect(t_cmd *lst,
			int *right_red_d, int *right_red);
void	search_for_redirect(t_cmd *lst, int *redirect_right);
void	check_redirect_r(t_cmd *lst);
void	check_redirect_l(t_cmd *lst);
void	null_redir_l(t_cmd *lst, int *redirect_l, int *redirect_d_l, int flag);
void	init_redir_l(t_cmd *lst, int redirect_left, int redirect_d_left);
void	parse_heredoc(t_cmd *lst, int *redirect_left, int *redirect_d_left);
void	search_for_redirect_l(t_cmd *lst, int *redirect_left);
int		check_malloc_for_envp(t_data *data, char *envp, int k);
void	flag_remove(t_cmd *new_list, int *env);
int		run_cmd(t_data *data, t_cmd *cmd_start);
void	run_cmd_child_out(t_data *data, t_cmd *cmd_start);
void	run_cmd_child_in_out(t_data *data, t_cmd *cmd_start);
void	run_cmd_child_in(t_data *data, t_cmd *cmd_start);
void	run_cmd_child_red_left(t_data *data, t_cmd *cmd_start);
void	run_cmd_child_red_left_part_two(t_data *data,
			t_cmd *cmd_start, int temppoint);
void	run_cmd_child_red_left_part_three(t_data *data,
			t_cmd *cmd_start, int temppoint);
void	run_cmd_child_red_right(t_data *data, t_cmd *cmd_start);
void	run_cmd_child_red_right_part_two(t_data *data,
			t_cmd *cmd_start, int temppoint);
void	run_cmd_child(t_data *data, t_cmd *cmd_start);
void	run_cmd_child_part_two(t_data *data, t_cmd *cmd_start);
void	run_cmd_child_else(t_data *data, t_cmd *cmd_start);
void	sigaction_handler(int SIGNUM, siginfo_t *siginfo, void *dunno);
void	signal_catcher(void);
void	sig_quit_catch(t_data *data);
int		check_builtins(t_cmd *cmd_start, t_data *data);
int		check_builtins_here(t_cmd *cmd_start);
int		check_builtins_firt_part(t_cmd *cmd_start, t_data *data);
char	*get_pwd(int flag, t_data *data);
char	*search_cmd_paths(t_data *data, char *cmd);
char	*cl_dir_and_ret_dir(DIR *dir, char *str);
void	search_wild_cards(t_cmd **start);
int		run_commands(t_data *data, t_cmd *cmd_start);
void	make_envp(t_data *data, char **envp);
void	env_concat_func(t_data *data, t_cmd *buf, int v, int *k);
int		envp_init(t_data *data, int *i, t_cmd **buf);
void	free_redirect(t_cmd *buf);
int		check_in_search_env(t_data *data, t_cmd **list,
			char *env, size_t *envlen);
void	write_unset(t_data *data, char *argv);
void	new_chain(t_cmd *temp, t_cmd **temp2);
char	*now_str_before(char *str, char c);
char	*get_argv_if_env_exist(char *str, char *env);
void	check_flags(t_cmd *lst, t_cmd *line);
void	check_flag_part_two(t_cmd *lst, t_cmd *line);
char	*check_home_token(char *str, t_data *data, t_cmd *line);
char	*check_wildcard(t_cmd **start, char *str);
int		get_cmd_parse_and_error(t_cmd *new_list, t_cmd **command_list,
			t_data *data);
char	*get_cmd_if_argv_doesnt_exist(char *str, t_cmd *ln, t_cmd *new_list);
void	checking_after_parsing(t_cmd *new_list, t_cmd *ln,
			char *str, int *argv);
void	parenthesis_parsing(t_cmd **ln, char **str, int *cmd);
int		parsing_init(t_cmd *ln, int *cmd, t_cmd **new_list, int *argv);
void	cmd_init_in_parsing(t_cmd *ln, int *cmd);
void	str_init_in_parsing(t_cmd **ln, char **str, t_data *data,
			t_cmd *new_list);
void	get_cmd(t_cmd *ln, t_cmd **command_list, t_data *data);
char	*char_add_to_str(char *str, char c);
char	*get_argv(char *str, t_cmd *line, t_data *data, char **redir_filename);
#endif