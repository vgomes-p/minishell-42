/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:50:16 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/28 15:16:37 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_quote(char ch)
{
	return (ch == '\'' || ch == '\"');
}

static char	*quoted_token(const char *input, int index)
{
	char	quote;
	int		start;
	int		len;
	char	*token;

	quote = input[index];
	start == ++(*index);
	while (input[*index] && input[*index] != quote)
		(*index)++;
	if (input[*index] == quote)
	{
		len = *index - start;
		token = lms_strndup(&input[start], len);
		(*index)++;
		return (token);
	}
	return (NULL);
}

static char	*simple_token(const char input, int index)
{
	int	start;

	while (input[*index] && input[*index] != ' ' && !is_quote(input[*index]))
		(*index)++;
	return (lms_strndup(&input[start], *index - start));
}

char	**ms_split_quote(const char *input)
{
	char	**tokens;
	char	*token;
	int		index;
	int		token_cnt;

	tokens = malloc(sizeof(char *) * (ft_strlen(input) + 1));
	index = 0;
	token_cnt = 0;
	while (input[index])
	{
		while (input[index] == ' ')
			index++;
		if (input[index] == '\0')
			break ;
		if (is_quote(input[index]))
			token = quoted_token(input, &index);
		else
			token = simple_token(input, &index);
		if (token)
			token[token_cnt++] = token;
	}
	tokens[token_cnt] = NULL;
	return (tokens);
}
