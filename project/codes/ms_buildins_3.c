/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buildins_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:32:54 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/15 16:32:57 by vgomes-p         ###   ########.fr       */
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
