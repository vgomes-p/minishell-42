/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:57:07 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/17 13:35:09 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMS_H
# define LIBMS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <malloc.h>
# include "../libft/libft.h"


void	lms_putchar(char ch);
void	lms_putstr(char *str);
int		lms_putenv(char ***env, char *str);
void	*lms_realloc(void *ptr, size_t nwsize);
int		lms_strcmp(const char *s1, const char *s2);
int		lms_unsetenv(char ***env, const char *name);
int		lms_setenv(char ***env, const char *name,
			const char *value, int overwrite);

#endif