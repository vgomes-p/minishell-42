/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/08 21:26:19 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_var(t_minishell *shell, char *str)
{
	char	*result;
	char	*var_start;
	char	*var_end;
	char	*var_name;
	char	*var_value;
	int		ind0;
	int		ind1;

	ind0 = 0;
	ind1 = 0;
	result = ft_calloc(ft_strlen(str) + 1024, sizeof(char)); // Buffer maior para evitar overflow
	if (!result)
		return (str);
	while (str[ind0])
	{
		if (str[ind0] == '\'' && !strchr(&str[ind0 + 1], '\'')) // Ignorar expansão em single quotes
		{
			result[ind1++] = str[ind0++];
			while (str[ind0] && str[ind0] != '\'')
				result[ind1++] = str[ind0++];
			if (str[ind0])
				result[ind1++] = str[ind0++];
		}
		else if (str[ind0] == '$' && str[ind0 + 1] && str[ind0 + 1] != ' ')
		{
			ind0++;
			var_start = &str[ind0];
			while (str[ind0] && (ft_isalnum(str[ind0]) || str[ind0] == '_'))
				ind0++;
			var_end = &str[ind0];
			var_name = ft_substr(var_start, 0, var_end - var_start);
			if (lms_strcmp(var_name, "?") == 0)
			{
				var_value = ft_itoa(shell->exit_stt);
				if (!var_value)
					var_value = ft_strdup("0");
			}
			else
			{
				var_value = getenv(var_name);
				if (!var_value)
					var_value = ft_strdup("");
				else
					var_value = ft_strdup(var_value);
			}
			ft_strlcat(result, var_value, ft_strlen(result) + ft_strlen(var_value) + 1);
			ind1 += ft_strlen(var_value);
			free(var_name);
			free(var_value);
		}
		else
			result[ind1++] = str[ind0++];
	}
	free(str);
	return (result);
}