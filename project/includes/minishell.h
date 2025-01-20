/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:13 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/20 17:57:06 by vgomes-p         ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
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

/* LIBMS FUNCTIONS */
void	lms_putchar(char ch);
void	lms_putstr(char *str);
int		lms_strcmp(const char *s1, const char *s2);
void	*lms_realloc(void *ptr, size_t nwsize);
char	*lms_strncpy(char *dest, const char *src, size_t n);

/* PARSING FUNCTIONS */
int		ms_quotes(const char *input, int start, char **output);

/* INTERACT FUNCTIONS */
void	ms_inishell(t_minishell *shell);
void	ms_interact0(t_minishell *shell);
int		lms_putenv(char ***env, char *str);
int		lms_setenv(char ***env, const char *name,
			const char *value, int overwrite);
int		lms_unsetenv(char ***env, const char *name);

/* BUILD_INS FUNCTIONS */
void	ms_cd(char **args);
void	ms_env(void);
void	ms_echo(char **args);
void	ms_exit(char **args, t_minishell *shell);
void	ms_env(void);
void	ms_export(char ***env, char **args);
void	ms_unset(char ***env, char **args);
void	ms_pwd(void);
void	ms_error(const char *msg, t_minishell *shell);
void	ms_process_buildin(char *input, t_minishell *shell);

#endif