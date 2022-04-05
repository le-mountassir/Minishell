/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:54:59 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/22 10:55:00 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join(char *dst, const char *src)
{
	char	*r;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	r = malloc(sizeof(char)
			* (ft_strlen(src) + ft_strlen(dst) + 1));
	if (!r)
		return (NULL);
	while (dst[++i])
		r[i] = dst[i];
	while (src[++j])
		r[i++] = src[j];
	r[i] = '\0';
	return (r);
}
