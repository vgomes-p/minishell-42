/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/06 13:39:36 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_var(char *token, t_minishell *shell)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	int		pos;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	pos = 0;
	while (token[pos])
	{
		if (token[pos] == '$' && (ft_isalnum(token[pos + 1]) || token[pos + 1] == '?'))
		{
			if (token[pos + 1] == '?')
			{
				var_value = ft_itoa(shell->exit_stt);
				pos += 2;
			}
			else
			{
				var_name = ft_strchr(token + pos, ' ');
				if (!var_name)
					var_name = ft_strdup(token + pos + 1);
				else
					var_name = ft_substr(token, pos + 1, var_name - (token + pos + 1));
				var_value = getenv(var_name);
				free(var_name);
				pos += ft_strlen(var_name) + 1;
			}
			result = lms_strjoin_free(result, var_value);
			free(var_value);
		}
		else
		{
			result = lms_strjoin_char(result, token[pos]);
			pos++;
		}
	}
	return (result);
}