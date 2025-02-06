/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:13 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/06 15:54:58 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* INCLUDES */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <curses.h>
# include <termcap.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
# include "libms/libms.h"
# include <readline/history.h>
# include <readline/readline.h>

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

/* STRUCTURES */
typedef struct s_minishell
{
	char	**env;
	size_t	env_size;
	char	*prompt;
	int		exit_stt;
	int		term_width;
	int		term_height;
	char	*error_message;
	int		error_code;
}	t_minishell;

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

typedef struct s_token
{
	char			*value;
	t_token_tp		type;
	struct s_token	*next;
}	t_token;

/* PROMPT */
char		**dup_env(char **envp, size_t *envsz);

void		welcome(void);
t_token		*tokening(char *input);
void		ms_prompt(t_minishell *shell);
char		**ms_split_quotes(const char *input);
char		**ms_split_quotes(const char *input);
t_token_tp	get_token_type(char *token, t_token *current, int is_first);

bool		is_quotes(char ch);
bool		is_operator(char *str);
void		free_tokens(t_token *tokens);
int			count_tokens(t_token *tokens);
void		cleanup_tokens(char **tokens, int token_cnt);
bool		valid_syntax(t_token *tokens);

int			find_envar(const char *var, char **envp);
void		update_envar(const char *var, int index0, char ***envp);
int			valid_name(const char *var);
void		export_err(const char *arg);

void		ms_env(t_minishell *shell);
void		ms_pwd(void);
void		ms_cd(char **args);
void		ms_echo(char **args);
void		ms_exit(char **args, t_minishell *shell);
void		ms_export(t_minishell *shell, char **args, char ***envp);
void		ms_unset(t_minishell *shell, char **args, char ***envp);

void		exec_extern(t_token *tokens, t_minishell *shell);
int			exec_builtin(t_token *tokens, t_minishell *shell);

#endif