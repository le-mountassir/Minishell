/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:47:02 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/21 17:47:03 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* normally it would return srclen + dstlen, 
* function has been modified to return src length only
*/

char	*ft_strcat(char *dst, const char *src, int k)
{
	size_t	j;

	j = 0;
	while (dst[k] && src[j])
		dst[k++] = src[j++];
	dst[k] = '\0';
	return (dst);
}
