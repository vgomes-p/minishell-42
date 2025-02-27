/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrodri <sthrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:33:52 by sthrodri          #+#    #+#             */
/*   Updated: 2025/02/27 13:00:06 by sthrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_fd(int *fd)
{
	fd[0] = -1;
	fd[1] = -1;
}

char	**redirect(t_minishell *shell, char **cmd, int *out, int *in)
{
	int		fd[2];
	int		cnt;
	char	**ret;

	cnt = 0;
	init_fd(fd);
	while (cmd[cnt])
		cnt++;
	ret = ft_calloc(cnt + 1, sizeof(char *));
	set_redirect(shell, cmd, fd, ret);
	if (fd[0] == -5 || fd[1] == -5)
		return (sfree(ret), NULL);
	if (fd[0] != -1)
		*in = (close(fd[0]), 1);
	if (fd[1] != -1 && (dup2(fd[1], STDOUT_FILENO) != -1))
		*out = (close(fd[1]), 1);
	return (ret);
}
