/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:13 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/21 15:41:02 by vgomes-p         ###   ########.fr       */
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

/* DEFINES */

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

/* UTILS FUNCTIONS */
void	ms_error(const char *msg, t_minishell *shell);

/* PARSING FUNCTIONS */
int		ms_quotes(const char *input, int start, char **output);

/* INTERWIN FUNCTIONS */
void	ms_inishell(t_minishell *shell);
void	ms_interact0(t_minishell *shell);

/* BUILD_INS FUNCTIONS */
void	ms_cd(char **args);
void	ms_env(void);
void	ms_echo(char **args);
void	ms_exit(char **args, t_minishell *shell);
void	ms_env(void);
void	ms_export(char ***env, char **args);
void	ms_unset(char ***env, char **args);
void	ms_pwd(void);
void	ms_tokenize_input(char *input, char ***tokens, t_minishell *shell);
void	ms_process_buildin(char *input, t_minishell *shell);

#endif