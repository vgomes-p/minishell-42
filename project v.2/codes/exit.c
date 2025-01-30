/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:21:22 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/29 18:45:25 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_exit(char **args, t_minishell *shell)
{
	int	stat;

	stat = 0;
	if (args[1])
		stat = ft_atoi(args[1]);
	shell->exit_stt = stat;
	free(shell->prompt);
	exit(stat);
}
