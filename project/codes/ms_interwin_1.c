/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_interwin_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:53:29 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/13 19:35:08 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_terminal(t_minishell *shell, char *buff)
{
	char	*term_type;
	char	*cm;

	term_type = getenv("TERM");
	if (!term_type || tgetent(buff, term_type) < 1)
	{
		ft_putstr_fd("Error: Unable to initialize terminal\n", 1);
		return (0);
	}
	shell->term_width = tgetnum("co");
	shell->term_height = tgetnum("li");
	cm = tgetstr("cm", NULL);
	if (!cm)
	{
		ft_putstr_fd("Error: Terminal does not support cursor movement\n", 1);
		return (0);
	}
	return (1);
}

static void	draw_horizontal_border(t_minishell *shell, int y_pos)
{
	int		index;
	char	*cm;

	cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, 0, y_pos), 1, ft_putchar);
	ft_putchar(1, '+');
	index = 1;
	while (index < shell->term_width - 1)
	{
		ft_putchar(1, '-');
		index++;
	}
	ft_putchar(1, '+');
	ft_putchar(1, '\n');
}

static void	draw_vertical_borders(t_minishell *shell)
{
	int		index;
	char	*cm;

	cm = tgetstr("cm", NULL);
	index = 1;
	while (index < shell->term_height - 2)
	{
		tputs(tgoto(cm, 0, index), 1, ft_putchar);
		ft_putchar(1, '|');
		tputs(tgoto(cm, shell->term_width - 1, index), 1, ft_putchar);
		ft_putchar(1, '|');
		ft_putchar(1, '\n');
		index++;
	}
}

void	ms_window(t_minishell *shell)
{
	char	buff[2048];

	if (!init_terminal(shell, buff))
		exit(1);
	draw_horizontal_border(shell, 0);
	draw_vertical_borders(shell);
	draw_horizontal_border(shell, shell->term_height - 1);
}
