/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:55:09 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:55:09 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	mksplit(char const *str, char ch, size_t cnt, char **substr)
{
	char	*str1;
	size_t	strini;
	size_t	strlen;

	while (str[cnt])
	{
		if (str[cnt] && str[cnt] != ch)
		{
			strini = cnt;
			while (str[cnt] && str[cnt] != ch)
				cnt++;
			strlen = (cnt - strini) + 1;
			str1 = malloc(sizeof(char) * strlen);
			ft_strlcpy(str1, &str[strini], strlen);
			*(char **)(substr++) = str1;
		}
		if (str[cnt] && str[cnt] == ch)
			while (str[cnt] && str[cnt] == ch)
				cnt++;
	}
	substr = NULL;
}

static size_t	cntwords(char const *str, char ch)
{
	size_t	words;

	words = 0;
	while (*str)
	{
		if (*str && *str != ch)
		{
			while (*str && *str != ch)
				str++;
			words++;
		}
		if (*str && *str == ch)
			while (*str && *str == ch)
				str++;
	}
	return (words + 1);
}

char	**ft_split(char const *str, char ch)
{
	size_t	numstrmk;
	char	**strsplit;

	if (!str)
		return (NULL);
	numstrmk = cntwords(str, ch);
	strsplit = ft_calloc((numstrmk), sizeof(char *));
	if (!strsplit)
		return (NULL);
	mksplit(str, ch, 0, strsplit);
	return (strsplit);
}
