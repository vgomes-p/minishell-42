/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:13 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/14 14:20:56 by vgomes-p         ###   ########.fr       */
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
	char	*prompt;
	int		exit_stt;
	int		term_width;
	int		term_height;
}	t_minishell;

/* UTILS FUNCTIONS */
void	ft_putchar(char ch);
void	ft_putstr(char *str);

/* FUNCTIONS */
void	ms_inishell(t_minishell *shell);
void	ms_interwin(t_minishell *shell);

#endif