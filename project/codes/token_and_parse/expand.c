/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/09 17:37:12 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_quoted_part(char *str, char *result, int *ind0, int *ind1)
{
	result[(*ind1)++] = str[(*ind0)++];
	while (str[*ind0] && str[*ind0] != '\'')
		result[(*ind1)++] = str[(*ind0)++];
	if (str[*ind0])
		result[(*ind1)++] = str[(*ind0)++];
}

static char	*extract_var_name(char *str, int *ind0)
{
	char	*var_start;
	char	*var_end;
	char	*var_name;

	var_start = &str[*ind0];
	while (str[*ind0] && (ft_isalnum(str[*ind0]) || str[*ind0] == '_'))
		(*ind0)++;
	var_end = &str[*ind0];
	var_name = ft_substr(var_start, 0, var_end - var_start);
	return (var_name);
}

static char	*get_var_value(t_minishell *shell, char *var_name)
{
	char	*var_value;

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
	return (var_value);
}

static void	handle_var(t_minishell *shell, char *str, char *result,
					int *indices)
{
	char	*var_name;
	char	*var_value;
	int		*ind0;
	int		*ind1;

	ind0 = &indices[0];
	ind1 = &indices[1];
	(*ind0)++;
	var_name = extract_var_name(str, ind0);
	var_value = get_var_value(shell, var_name);
	ft_strlcat(result, var_value, ft_strlen(result)
		+ ft_strlen(var_value) + 1);
	*ind1 += ft_strlen(var_value);
	free(var_name);
	free(var_value);
}

char	*expand_var(t_minishell *shell, char *str)
{
	char	*result;
	int		indices[2];

	indices[0] = 0;
	indices[1] = 0;
	result = ft_calloc(ft_strlen(str) + 1024, sizeof(char));
	if (!result)
		return (str);
	while (str[indices[0]])
	{
		if (str[indices[0]] == '\'' && !strchr(&str[indices[0] + 1], '\''))
			handle_quoted_part(str, result, &indices[0], &indices[1]);
		else if (str[indices[0]] == '$' && str[indices[0] + 1]
			&& str[indices[0] + 1] != ' ')
			handle_var(shell, str, result, indices);
		else
			result[indices[1]++] = str[indices[0]++];
	}
	free(str);
	return (result);
}
