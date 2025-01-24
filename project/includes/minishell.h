/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:13 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/24 15:35:41 by vgomes-p         ###   ########.fr       */
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
# define RESET		"\033[0m"
# define RED		"\033[1;31m"
# define CYAN		"\033[1;36m"
# define PINK		"\033[1;35m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define REWHITE	"\033[1;7;97m"
# define RECYAN		"\033[1;7;36m"
# define REPINK		"\033[1;7;35m"
# define RERED		"\033[1;7;31m"
# define REGREEN	"\033[1;7;32m"
# define REYELLOW	"\033[1;7;33m"

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

/* PROMPT */
void	welcome(void);
void	ms_prompt(t_minishell *shell);

#endif