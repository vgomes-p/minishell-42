/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:14:24 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/04 16:22:12 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_exit(char **args, t_minishell *shell)
{
	int	stat;

	stat = 0;
	if (args[1] && args[2])
	{
		ft_putstr_fd(RED "exit: too many arguments\n" RESET, 2);
		shell->exit_stt = 1;
		return ;
	}
	if (args[1])
	{
		if (!lms_isnum(args[1]))
		{
			ft_putstr_fd(RED "exit: the argument " ORANGE "\"", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd("\"" RED " is not a valid integer\n", 2);
			shell->exit_stt = 2;
			free(shell->prompt);
			return ;
		}
		stat = ft_atoi(args[1]);
	}
	shell->exit_stt = stat;
	ft_putstr_fd(PINK "\n\n\nSee you soon, goodbye!\n\n\n" RESET, 1);
	free(shell->prompt);
	exit(stat);
}
