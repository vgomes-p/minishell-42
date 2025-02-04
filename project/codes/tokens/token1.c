/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:19:43 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/04 16:53:55 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static bool	process_quotes(const char *input, int *index, bool *in_quotes,
						char *quote_ch)
{
	while (input[*index] && (*in_quotes || input[*index] != ' '))
	{
		if (is_quotes(input[*index]))
		{
			if (!*in_quotes)
			{
				*in_quotes = true;
				*quote_ch = input[*index];
			}
			else if (input[*index] == *quote_ch)
				*in_quotes = false;
		}
		(*index)++;
	}
	if (*in_quotes)
	{
		printf(RED "Error: quotes not closed" RESET);
		return (false);
	}
	return (true);
}

static char	*extract_token(const char *input, int *index)
{
	int		start;
	bool	in_quotes;
	char	quote_ch;

	start = *index;
	in_quotes = false;
	quote_ch = '\0';
	if (!process_quotes(input, index, &in_quotes, &quote_ch))
		return (NULL);
	return (clean_token(&input[start], *index - start));
}

static char	**process_tokens(const char *input, char **tokens)
{
	char	*token;
	int		index0;
	int		token_cnt;

	index0 = 0;
	token_cnt = 0;
	while (input[index0])
	{
		while (input[index0] == ' ')
			index0++;
		if (input[index0] == '\0')
			break ;
		token = extract_token(input, &index0);
		if (token)
			tokens[token_cnt++] = token;
		else
		{
			cleanup_tokens(tokens, token_cnt);
			return (NULL);
		}
	}
	tokens[token_cnt] = NULL;
	return (tokens);
}

char	**ms_split_quotes(const char *input)
{
	char	**tokens;

	tokens = ft_calloc(ft_strlen(input) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	return (process_tokens(input, tokens));
}
