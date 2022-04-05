/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:55:44 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/22 10:55:45 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	j = 0;
	srclen = ft_strlen(src);
	while (dst[i] && i < size)
		i++;
	dstlen = i;
	while (src[j] && i + 1 < size)
		dst[i++] = src[j++];
	if (dstlen < size)
		dst[i] = '\0';
	return (srclen + dstlen);
}
