/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:43:44 by kaisogai          #+#    #+#             */
/*   Updated: 2025/10/02 10:55:55 by kaisogai         ###   ########.fr       */
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
# include <unistd.h>

# define DUP2 "dup2"
# define PIPE "pipe"
# define FORK "fork"
# define ACCESS "access"
# define WAITPID "waitpid"
# define EXECVE "execve"
# define MALLOC "malloc"
# define PIPE_SIGN "|"

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

t_cmd				*parse_input(char *input);
int					output(pid_t pid, char **argv, int d_pipe[2], char **envp);
int					input_child_process(char **argv, int d_pipe[2],
						char **envp);
int					output_child_process(char **argv, int pipe_in, char **envp);
void				error_exit(char *error_target);
char				**tokenize(const char *str);
void				free_split(char **args);
void				handle_command_path_error(char **args,
						int has_permission_error, char **paths);
char				*build_command_path(char **args, char **envp);
void				execve_error_exit(char *cmd);
int					is_quote(char c);
int					free_strs(char **strs, int count);
int					is_delimiter(char str);
int					is_letter(const char str);
int					is_shift_operator(const char *str);
void				copy_strs(int word_length, char *strs, const char *str);
int					create_new_token(char **strs, const char *str, t_split s);

int					ft_strcmp(char *s1, char *s2);
char				*expand(char *str);
char				*expand_with_var(char *str);
char				**expand_all(char **strs);
int					setup_heredoc(char *target);
void				ft_echo(char **args);
void				ft_cd(char *path);

#endif
