/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:59:14 by ahel-mou          #+#    #+#             */
/*   Updated: 2021/11/11 15:52:45 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*srx;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	dst = dest;
	srx = (unsigned char *)src;
	while (i < n)
	{
		dst[i] = srx[i];
		i++;
	}
	return (dest);
}
