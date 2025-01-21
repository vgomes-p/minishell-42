/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:46:03 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/21 14:47:43 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_error(const char *msg, t_minishell *shell)
{
	if (shell)
		shell->error_message = ft_strdup(msg);
	ft_putstr_fd("Error!\n", 2);
}
