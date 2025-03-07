/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lms_joinstr_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:15:00 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/22 17:16:15 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*lms_strjoin_free(char *str1, char *str2)
{
	char	*joined;

	joined = ft_strjoin(str1, str2);
	free(str1);
	return (joined);
}
