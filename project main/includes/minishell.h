/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:13 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/03 19:16:50 by vgomes-p         ###   ########.fr       */
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
# include "mscolor.h"
# include <termcap.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
# include "libms/libms.h"
# include <readline/history.h>
# include <readline/readline.h>

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
void		ms_prompt(t_minishell *shell);
t_token		*tokening(char *input);
t_token_tp	get_token_type(char *token, t_token *current, int is_first);
char		**ms_split_quotes(const char *input);
bool		valid_syntax(t_token *tokens);
char		**ms_split_quotes(const char *input);

void		free_tokens(t_token *tokens);
int			count_tokens(t_token *tokens);

void		ms_cd(char **args);
void		ms_echo(char **args);
void		ms_exit(char **args, t_minishell *shell);
void		ms_pwd(void);
void		ms_env(void);

void		exec_extern(t_token *tokens, t_minishell *shell);
int			exec_builtin(t_token *tokens, t_minishell *shell);

#endif