/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:19:43 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/05 15:21:22 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*clean_token(const char *str, int len)
{
	char	*cleaned;
	int		pos;
	int		nwpos;

	cleaned = malloc(len + 1);
	pos = 0;
	nwpos = 0;
	if (!cleaned)
		return (NULL);
	while (pos < len)
	{
		if (!is_quotes(str[pos]))
		{
			cleaned[nwpos++] = str[pos];
		}
		pos++;
	}
	cleaned[nwpos] = '\0';
	return (cleaned);
}

static bool	process_quotes(const char *input, int *pos, bool *in_quotes,
						char *quote_ch)
{
	while (input[*pos] && (*in_quotes || input[*pos] != ' '))
	{
		if (is_quotes(input[*pos]))
		{
			if (!*in_quotes)
			{
				*in_quotes = true;
				*quote_ch = input[*pos];
			}
			else if (input[*pos] == *quote_ch)
				*in_quotes = false;
		}
		(*pos)++;
	}
	if (*in_quotes)
	{
		printf(RED "Error: quotes not closed" RESET);
		return (false);
	}
	return (true);
}

static char	*extract_token(const char *input, int *pos)
{
	int		start;
	bool	in_quotes;
	char	quote_ch;

	start = *pos;
	in_quotes = false;
	quote_ch = '\0';
	if (!process_quotes(input, pos, &in_quotes, &quote_ch))
		return (NULL);
	return (clean_token(&input[start], *pos - start));
}

static char	**process_tokens(const char *input, char **tokens)
{
	char	*token;
	int		pos;
	int		token_cnt;

	pos = 0;
	token_cnt = 0;
	while (input[pos])
	{
		while (input[pos] == ' ')
			pos++;
		if (input[pos] == '\0')
			break ;
		token = extract_token(input, &pos);
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
