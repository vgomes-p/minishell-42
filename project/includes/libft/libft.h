/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:57:07 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:57:07 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <malloc.h>

/* MANDATORY LIBFT */
char	*ft_itoa(int num);
int		ft_isalpha(int ch);
int		ft_toupper(int ch);
int		ft_tolower(int ch);
int		ft_isdigit(int dig);
int		ft_isascii(int var);
int		ft_isprint(int var);
int		ft_isalnum(int chdig);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *var);
char	*ft_strdup(const char *str0);
void	ft_putnbr_fd(int num, int fd);
void	ft_putchar_fd(char ch, int fd);
void	ft_bzero(void *str, size_t nby);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
char	*ft_strchr(const char *str, int ch);
char	*ft_strrchr(const char *str, int ch);
char	**ft_split(char const *str, char ch);
void	*ft_calloc(size_t num_el, size_t numby);
char	*ft_strtrim(char const *str0, char const *set);
void	*ft_memset(void *buffer, int value, size_t len);
char	*ft_strjoin(char const *str0, char const *str1);
void	*ft_memchr(const void *str, int ch, size_t numby);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t numby);
void	*ft_memmove(void *dest, const void *src, size_t numby);
size_t	ft_strlcat(char *dest, const char *src, size_t destsz);
void	ft_striteri(char *str, void (*ftn)(unsigned int, char*));
int		ft_memcmp(const void *str0, const void *str1, size_t numby);
char	*ft_strnstr(const char *big, const char *ltl, size_t lench);
char	*ft_substr(char const *str, unsigned int start, size_t len);
int		ft_strncmp(const char *str0, const char *str1, size_t numby);
char	*ft_strmapi(char const *str, char (*ftn)(unsigned int, char));

#endif