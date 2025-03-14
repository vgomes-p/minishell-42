/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:57:07 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/06 13:39:47 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMS_H
# define LIBMS_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <malloc.h>
# include "../libft/libft.h"

void	lms_putchar(char ch);
void	lms_putstr(char *str);
int		lms_isnum(const char *str);
char	*lms_strndup(const char *str, size_t n);
char	*lms_strjoin_free(char *str1, char *str2);
int		lms_strcmp(const char *s1, const char *s2);
char	*lms_strjoin_char(char const *str0, char ch);
char	*lms_strncpy(char *dest, const char *src, size_t n);
void	*lms_realloc(void *ptr, size_t oldsz, size_t nwsize);
char	*lms_strstr(const char *haystack, const char *needle);

#endif