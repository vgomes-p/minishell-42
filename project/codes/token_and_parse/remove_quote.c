/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:14:43 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/17 16:14:43 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_all_quotes(char *str)
{
	char	*result;
	int		ind0;
	int		ind1;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	ind0 = 0;
	ind1 = 0;
	while (str[ind0])
	{
		if (str[ind0] != '\'' && str[ind0] != '"')
			result[ind1++] = str[ind0];
		ind0++;
	}
	result[ind1] = '\0';
	free(str);
	return (result);
}
