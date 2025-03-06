/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/06 15:31:56 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_exit_status(t_minishell *shell, int *pos)
{
	char	*var_value;

	var_value = ft_itoa(shell->exit_stt);
	*pos += 2;
	return (var_value);
}

static char	*extract_var_name(char *token, int pos)
{
	char	*var_name;
	char	*space_ptr;

	space_ptr = ft_strchr(token + pos, ' ');
	if (!space_ptr)
		var_name = ft_strdup(token + pos + 1);
	else
		var_name = ft_substr(token, pos + 1, space_ptr - (token + pos + 1));
	return (var_name);
}

static char	*expand_regular_var(char *token, int *pos, t_minishell *shell)
{
	char	*var_name;
	char	*var_value;
	int		index;

	var_name = extract_var_name(token, *pos);
	if (!var_name)
		return (NULL);
	index = find_envar(var_name, shell->env);
	if (index != -1)
		var_value = ft_strdup(ft_strchr(shell->env[index], '=') + 1);
	else
		var_value = ft_strdup("");
	*pos += ft_strlen(var_name) + 1;
	free(var_name);
	return (var_value);
}

static char	*handle_dollar_var(char *token, int *pos, t_minishell *shell)
{
	char	*var_value;

	if (token[*pos + 1] == '?')
		var_value = expand_exit_status(shell, pos);
	else
		var_value = expand_regular_var(token, pos, shell);
	return (var_value);
}

char	*expand_var(char *token, t_minishell *shell)
{
	char	*result;
	char	*var_value;
	int		pos;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	pos = 0;
	while (token[pos])
	{
		if (token[pos] == '$' && (ft_isalnum(token[pos + 1]) || 
			token[pos + 1] == '?'))
		{
			var_value = handle_dollar_var(token, &pos, shell);
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