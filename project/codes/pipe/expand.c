/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrodri <sthrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/21 13:33:17 by sthrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishel.h"

void	print_variable(char *arg)
{
	char	*var_name;
	char	*value;

	var_name = arg + 1;
	value = getenv(var_name);
	if (value)
		ft_putstr_fd(value, STDOUT_FILENO);
}

void	print_argument(char *arg)
{
	int		in_double_quotes;
	int		in_single_quotes;
	int		j;

	in_double_quotes = 0;
	in_single_quotes = 0;
	j = 0;
	while (arg[j])
	{
		if (arg[j] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (arg[j] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (arg[j] == '$' && !in_single_quotes)
		{
			print_variable(&arg[j]);
			while (arg[j + 1] && (ft_isalnum(arg[j + 1]) || arg[j + 1] == '_'))
				j++;
		}
		else
			ft_putchar_fd(arg[j], STDOUT_FILENO);
		j++;
	}
}

void	print_echo_args(char **args, int start)
{
	int	i;

	i = start;
	while (args[i])
	{
		print_argument(args[i]);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}
