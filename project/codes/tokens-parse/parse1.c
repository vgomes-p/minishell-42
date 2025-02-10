/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:40:40 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/10 19:04:33 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_parser(t_token **head, char *str)
{
	char	**cmdls;
	char	**args;
	int		pos;
	int		index1;

	cmdls = ms_lexer(str);
	if (!cmdls)
	{
		ft_putstr_fd(ORANGE "-minishell: parser: unclosed quotes\n" RESET, 2);
		return (1);
	}
	pos = -1;
	while (cmdls[++pos])
	{
		index1 = -1;
		args = split_args(cmdls[pos]);
		while (args[index1])
			add_token(head, args[index1]);
		free(args);
	}
	if (pos > 0)
		check_pipe(cmdls[pos - 1], head);
	free(cmdls);
	define_type(head);
	return (valid_syntax(*head) ? 0 : 1);
}

void	check_pipe(char *cmd, t_token **head)
{
	char	*input;

	if (ft_strncmp(cmd, "|") == 0)
	{
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd(RED "minishell: syntax error: unexpected end of file\n" RESET, 2);
			return ;
		}
		ms_parser(head, input);
		free(input);
	}
}

char **lexer(char *input)
{
	(void)input;
}
