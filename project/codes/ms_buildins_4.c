/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buildins_8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:11:40 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/21 15:33:44 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_quotes(char *input, int *pos, int *tokencnt, char ***tokens, t_minishell *shell)
{
	char	*quote_content;
	int		finalquote;

	quote_content = NULL;
	finalquote = ms_quotes(input, *pos + 1, &quote_content);
	if (finalquote == -1)
	{
		ms_error("unmatched quotes detected", shell);
		return ;
	}
	(*tokencnt)++;
	*tokens = lms_realloc(*tokens, sizeof(char *) * ((*tokencnt) + 1));
	(*tokens)[*tokencnt - 1] = quote_content;
	(*tokens)[*tokencnt] = NULL;
	*pos += ft_strlen(quote_content) + 2;
}

static void	handle_non_quotes(char *input, int *pos, int *tokencnt, char ***tokens)
{
	int		start;
	char	*tokenstt;

	start = *pos;
	while (input[*pos] && input[*pos] != ' ' && input[*pos] != '\'' && input[*pos] != '\"')
	{
		(*pos)++;
	}
	tokenstt = lms_strndup(input + start, *pos - start);
	(*tokencnt)++;
	*tokens = lms_realloc(*tokens, sizeof(char *) * ((*tokencnt) + 1));
	(*tokens)[*tokencnt - 1] = tokenstt;
	(*tokens)[*tokencnt] = NULL;
}

static void	process_input(char *input, char ***tokens, t_minishell *shell)
{
	int	pos;
	int	tokencnt;

	pos = 0;
	tokencnt = 0;
	*tokens = NULL;
	while (input[pos])
	{
		if (input[pos] == ' ')
		{
			pos++;
			continue;
		}
		if (input[pos] == '\'' || input[pos] == '\"')
			handle_quotes(input, &pos, &tokencnt, tokens, shell);
		else
			handle_non_quotes(input, &pos, &tokencnt, tokens);
		if (!*tokens)
			return ;
	}
}

void	ms_tokenize_input(char *input, char ***tokens, t_minishell *shell)
{
	process_input(input, tokens, shell);
}

