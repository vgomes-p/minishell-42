/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:13:56 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/12 17:56:13 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_env(t_minishell *shell)
{
	int	curr_arg;

	curr_arg = 0;
	while (shell->env && shell->env[curr_arg])
	{
		ft_putendl_fd(shell->env[curr_arg], STDOUT_FILENO);
		curr_arg++;
	}
}
