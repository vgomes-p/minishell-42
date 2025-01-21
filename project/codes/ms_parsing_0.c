/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:49:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/21 14:41:18 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_quotes(const char *input, int start, char **output)
{
	int		pos;
	char	quote;

	pos = start;
	quote = input[start - 1];
	while (input[pos] != '\0')
	{
		if (input[pos] == quote)
		{
			*output = (char *)malloc(pos - start);
			if (!(*output))
				return (-1);
			lms_strncpy(*output, input + start, pos - start);
			(*output)[pos - start] = '\0';
			return (1);
		}
		pos++;
	}
	return (-1);
}
