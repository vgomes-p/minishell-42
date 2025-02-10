/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:26:31 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/10 18:40:11 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_args(char *input)
{
	char	**args;
	int		index;
	int		quotes;

	index = -1;
	quotes = 0;
	while (input[++index])
	{
		if (input[index] == ' ' && !quotes)
			input[index] = SEP;
		else if (input[index] == '\"' || input[index] == '\'')
			quotes = !quotes;
	}
	args = ms_split_quotes(input);
	return (args);
}
