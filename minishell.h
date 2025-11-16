/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:43:44 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/16 14:40:06 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define DUP2 "dup2"
# define PIPE "pipe"
# define FORK "fork"
# define ACCESS "access"
# define WAITPID "waitpid"
# define EXECVE "execve"
# define MALLOC "malloc"
# define PIPE_SIGN "|"

extern char			**environ;
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR
}					t_node_type;

typedef struct s_split
{
	int				i;
	int				j;
	int				token_len;
}					t_split;

typedef enum e_redir_type
{
	R_NONE,
	R_IN,
	R_OUT,
	R_APP,
	R_HDOC
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_var
{
	int				start;
	int				end;
}					t_var;


typedef struct s_fds
{
	int				read_fd;
	int				write_fd;
}					t_fds;

typedef struct s_pipe_fds
{
	int				prev_read_fd;
	int				pipe_fd[2];
}					t_pipe_fds;

void				parent_process(t_pipe_fds *pipe_fds, pid_t pid,
						int *status);
int					run_normal_command(t_cmd *cmds, t_pipe_fds *pipe_fds,
						t_env **env_list, int *exit_status);
int					run_last_command(t_cmd *cmds, t_pipe_fds *pipe_fds,
						t_env **env_list, int *exit_status);
void				append_arg(t_cmd *cmd, char *token);
t_cmd				*parse_input(char *input);
void				free_all(char **array);
t_cmd				*new_cmd(void);
void				cmd_add_back(t_cmd **lst, t_cmd *new);
t_redir				*new_redir(t_redir_type type, char *target);
t_redir_type		get_redir_type(char *token);
int					is_redirect(char *s);
int					is_valid_target(char *s);
void				redir_add_back(t_redir **lst, t_redir *new);
t_cmd				*check_current_cmd(t_cmd **head_cmd, t_cmd **current);
void 				syntax_error();
int					output(pid_t pid, char **argv, int d_pipe[2], char **envp);
int					input_child_process(char **argv, int d_pipe[2],
						char **envp);
int					output_child_process(char **argv, int pipe_in, char **envp);
void				error_exit(char *error_target);
char				**tokenize(const char *str);
void				free_split(char **args);
void				handle_command_path_error(t_cmd *cmds,
						int has_permission_error, char **paths);
char				*build_command_path(t_cmd *cmds, t_env **env_list);
void				execve_error_exit(char *cmd);
int					is_quote(char c);
int					free_strs(char **strs, int count);
int					is_delimiter(char str);
int					is_letter(const char str);
int					is_shift_operator(const char *str);
void				copy_strs(int word_length, char *strs, const char *str);
int					create_new_token(char **strs, const char *str, t_split s);

int					ft_strcmp(char *s1, char *s2);
char				*store_before_dollor(char *result, char *str,
						int dollar_pos);
char				*ft_getenv(t_env *env_list, char *key);
char				*expand_and_add_var(char *result, char *str, t_var var, t_env *env_list);
char				*add_after_var(char *result, char *str, int var_end,
						t_env *env_list, int exit_status);
char				*expand_with_var(char *str, t_env *env_list, int exit_stat);
char				*expand_token(char *str, t_env *env_list, int exit_status);
char				**expand_all(char **strs, t_env *env_list, int exit_status);
char				**expand_args(char **args, t_env *env_list,
						int exit_status);
t_fds				expand_redirs(t_redir *redirs, t_env *env_list,
						int exit_status);
int					setup_heredoc(char *target);
int					ft_echo(char **args);
int					ft_cd(char *path, t_env **env_list);
int					ft_pwd(void);
int					ft_unset(char **arg, t_env **env_list);
void				message_exit(char *message, int exit_type);

t_env				*new_env(char *key, char *value);
void				add_env_back(t_env **lst, t_env *new);
t_env				*init_env(void);
int					ft_env(char **args, t_env *env_list);
int					handle_export_error(char *invalid_key);
int					is_valid_export_key(const char *key);
int					ft_export(char **args, t_env **env_list);
void				ft_exit(t_cmd *cmds, t_env **env_list);
void				free_exit(void *target);
int					exec_builtin_fn(t_cmd *cmds, t_env **env_list,
						int exit_status);
void				free_all(char **array);
void				free_cmds(t_cmd *cmds);
void				free_key_value(char *key, char *value);
char				**env_list_to_envp(t_env *env_list);
void				sig_int_handler(int signo);

#endif
