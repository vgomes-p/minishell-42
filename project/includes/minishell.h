/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:13 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/28 15:21:37 by vgomes-p         ###   ########.fr       */
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

typedef struct s_exec_tree
{
	char				*cmd;
	t_token_tp			type;
	struct s_exec_tree	*left;
	struct s_exec_tree	*right;
}	t_exec_tree;

/* PROMPT */
void	welcome(void);
void	ms_prompt(t_minishell *shell);
t_token	*tokening(char *input);
bool	valid_syntax(t_token *tokens);
char	**ms_split_quote(const char *input);

#endif