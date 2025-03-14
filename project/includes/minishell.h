/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:13 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/14 18:33:08 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* INCLUDES */
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <curses.h>
# include <termcap.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
# include "libms/libms.h"
# include <readline/history.h>
# include <readline/readline.h>

/* DEFINES */
# ifndef SEP
#  define SEP -1
# endif

/* DEFINE COLORS */
# define RESET		"\001\033[0m\002"
# define RED		"\001\033[1;31m\002"
# define GREEN		"\001\033[1;32m\002"
# define YELLOW		"\001\033[1;33m\002"
# define PINK		"\001\033[1;35m\002"
# define CYAN		"\001\033[1;36m\002"
# define ORANGE		"\001\033[1;38;5;214m\002"
# define RERED		"\001\033[1;7;31m\002"
# define REYELLOW	"\001\033[1;7;33m\002"
# define REGREEN	"\001\033[1;7;32m\002"
# define REPINK		"\001\033[1;7;35m\002"
# define RECYAN		"\001\033[1;7;36m\002"
# define REORANGE	"\001\033[1;7;38;5;214m\002"
# define REWHITE	"\001\033[1;7;97m\002"

/* ENUM */
typedef enum e_token_tp
{
	CMD,
	ARG,
	PIPE,
	APPEND,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	SYNTAX_ERROR,
}	t_token_tp;

/* STRUCTURES */
typedef struct s_token
{
	char			*value;
	t_token_tp		type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_exec
{
	t_token	*temp;
	char	**cmd;
	int		**fd;
	int		stts;
	pid_t	*pid;
	int		nbr_pros;
	t_token	*tokens_head;
}	t_exec;

typedef struct s_expand
{
	char	**hold_str;
	int		exec;
	int		start;
	int		end;
	int		quotes;
	int		exec_n;
	int		i;
}	t_expand;

typedef struct s_cmd_exec
{
	char	**cmd;
	int		**fd;
	int		pos;
	t_token	*cmd_tokens;
}	t_cmd_exec;

typedef struct s_minishell
{
	int		pid;
	char	**env;
	char	*prompt;
	size_t	env_size;
	int		exit_stt;
	int		term_width;
	int		error_code;
	int		term_height;
	char	*error_message;
	t_token	*tokens;
}	t_minishell;

/* GLOBAL VAR */
extern t_minishell	*g_shell;

/* BUILDINS DIR */
//bi_utils
int			find_envar(const char *var, char **envp);
void		update_envar(const char *var, int index0, char ***envp);
int			valid_name(const char *var);
//bi_utils1
void		export_err(const char *arg);
//echo
void		ms_echo(char **args);
//pwd
void		ms_pwd(t_minishell *shell);
//ms_env
void		ms_env(t_minishell *shell);
//cd
void		ms_cd(char **args, t_minishell *shell);
//exit
void		ms_exit(char **args, t_minishell *shell);
//unset
void		ms_unset(t_minishell *shell, char **args, char ***envp);
//export
void		ms_export(t_minishell *shell, char **args, char ***envp);

/* EXEC DIR */
// cmd_path
char		*get_full_path(char *cmd, char **path_dir);
char		*find_exec_path(char *cmd, char **envp);
//exec_family
int			exec_parent(t_minishell *shell, int nb_pros, char **cmd, int **fd);
void		exec_child(t_minishell *shell, t_exec *exec, int pos);
void		child(t_minishell *shell, t_cmd_exec *exec);
//exec_externs
t_exec		init_exec(t_minishell *shell, t_token *tokens);
void		cleanup_processes(t_exec *exec, t_minishell *shell, int cmd_pos);
void		exec_cmd(t_minishell *shell);
//exec_buildins
int			exec_builtin(t_token *tokens, t_minishell *shell,
				int **fd, int pos);
//is_utils
int			is_buildin(char *token);
int			is_redir(t_token *token);
int			is_dir(t_minishell *shell, char *cmd);

//exec_utils_0
char		**prepare_args(t_token *tokens);
void		cls_fd(int **fd);
//exec_utils_1
void		exec_extern(char **cmd, char **envp);
void		clean_child_res(t_minishell *shell, char **cmd, int **fd, int code);
void		handle_invalid_file(t_minishell *shell);
//exec_utils_2
t_token		*get_next_cmd(t_token **tokens);
void		file_errmsg(t_minishell *shell, char *cmd);

/* MAIN DIR */
//prompt_utils.c
void		welcome(void);
//prompt.c
void		ms_prompt(t_minishell *shell);

/* REDIR DIR */
//redirects
void		ms_redirs(t_minishell *shell, t_token *tokens, int **fd, int pos);
//heredoc
void		process_heredoc(t_minishell *shell, t_token *token);

/* TOKEN_AND_PARSE DIR */
//token
t_token		*mktoken(char *value, t_token_tp type);
char		**ms_split_quotes(const char *input);
t_token		*create_token_list(char **split, t_token *head);
t_token		*tokening(char *input);
//token_utils_0
bool		process_quotes(const char *input, int *pos, bool *in_quotes,
				char *quote_ch);
char		**process_tokens(const char *input, char **tokens);
char		*extract_token(const char *input, int *pos);
t_token_tp	get_token_type(char *token, t_token *current, int is_first);
//token_utils_1
bool		is_quotes(char ch);
bool		is_operator(char *str);
void		cleanup_tokens(char **tokens, int token_cnt);
int			count_tokens(t_token *tokens);
char		*clean_token(const char *str, int len);
//token_utils_2
char		**tokens_matrix(t_token *token);
t_token		*cpy_token_ls(t_token *tokens);
void		addtoken_ls(t_token *list, t_token *new_token);
//parse
int			parser(t_token **head, char *str);
//syntax
bool		valid_syntax(t_token *tokens);
//expand
char		*expand_var(t_minishell *shell, char *str);

/* UTILS DIR */
//all_free_0
void		free_tokens(t_token *tokens);
void		sfree(char **split);
char		*free_ptr(char *ptr);
void		sfree_int(int **fd);
void		free_matrix(char ***matrix);
//all_free_1
void		free_env(char **env);

//utils
char		**dup_env(char **envp, size_t *envsz);
void		interactive_signal_handler(int sig);

#endif