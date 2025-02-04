/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:19:43 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/04 16:19:46 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_quotes(char ch)
{
	return (ch == '\'' || ch == '\"');
}

static char	*clean_token(const char *str, int len)
{
	char	*cleaned;
	int		index0;
	int		index1;

	cleaned = malloc(len + 1);
	index0 = 0;
	index1 = 0;

	if (!cleaned)
		return (NULL);
	while (index0 < len)
	{
		if (!is_quotes(str[index0]))
		{
			cleaned[index1++] = str[index0];
		}
		index0++;
	}
	cleaned[index1] = '\0';
	return (cleaned);
}

static char	*extract_token(const char *input, int *index)
{
	int		start;
	bool	in_quotes;
	char	quote_ch;

	start = *index;
	in_quotes = false;
	quote_ch = '\0';
	while (input[*index] && (in_quotes || input[*index] != ' '))
	{
		if (is_quotes(input[*index]))
		{
			if (!in_quotes)
			{
				in_quotes = true;
				quote_ch = input[*index];
			}
			else if (input[*index] == quote_ch)
			{
				in_quotes = false;
			}
		}
		(*index)++;
	}
	if (in_quotes)
	{
		printf(RED "Error: quotes not closed" RESET);
		return (NULL);
	}
	return (clean_token(&input[start], *index - start));
}

char	**ms_split_quotes(const char *input)
{
	char	**tokens;
	char	*token;
	int		index0;
	int		token_cnt;
	int		index1;

	index0 = 0;
	token_cnt = 0;
	tokens = ft_calloc(ft_strlen(input) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (input[index0])
	{
		while (input[index0] == ' ')
			index0++;
		if (input[index0] == '\0')
			break ;
		token = extract_token(input, &index0);
		if (token)
		{
			tokens[token_cnt++] = token;
		}
		else
		{
			index1 = 0;
			while (index1 < token_cnt)
			{
				free(tokens[index1]);
				index1++;
			}
			free(tokens);
			return (NULL);
		}
	}
	tokens[token_cnt] = NULL;
	return (tokens);
}
