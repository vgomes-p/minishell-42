/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lms_putenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:00:21 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/16 17:13:57 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

int	lms_putenv(char ***env, char *str)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	if (!env || !str)
		return (-1);
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return (-1);
	*equal_sign = '\0';
	name = str;
	value = equal_sign + 1;
	return (lms_setenv(env, name, value, 1));
}
