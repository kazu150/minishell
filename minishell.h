/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:43:44 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/13 13:16:33 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define DUP2 "dup2"
# define PIPE "pipe"
# define FORK "fork"
# define ACCESS "access"
# define WAITPID "waitpid"
# define EXECVE "execve"
# define MALLOC "malloc"
# define PIPE_SIGN "|"

int					output(pid_t pid, char **argv, int d_pipe[2], char **envp);
int					input_child_process(char **argv, int d_pipe[2],
						char **envp);
int					output_child_process(char **argv, int pipe_in, char **envp);
void				error_exit(char *error_target);
char				**ft_split(const char *str, char c);
void				free_split(char **args);
char				*ft_strjoin(const char *str1, const char *str2);
void				handle_command_path_error(char **args,
						int has_permission_error, char **paths);
char				*build_command_path(char **args, char **envp);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *s);
void				execve_error_exit(char *cmd);
int					is_qt(char c);
int					free_strs(char **strs, int count);

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR
}					t_node_type;

typedef struct s_splt
{
	int				i;
	int				j;
	int				w_len;
	int				inside_qt;
	char			current_qt;
}					t_splt;

typedef enum e_redir_type
{
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

#endif
