/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:58:56 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/25 17:54:57 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_numlen(long n);
char	**ft_splitpath(char *s, char c);
size_t	ft_intlen(long x);
int		white_spaces(char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isnumber(char *s);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
size_t	td_arr_len(char **str);
char	*ft_strcat(char *dst, const char *src, int k);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_join(char *dst, const char *src);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	ft_putstr(char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	ft_putstr_fd(char const *s, int fd);
long	ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putnbr_fd(int nb, int fd);
int		ft_isprint(int c);
#endif
