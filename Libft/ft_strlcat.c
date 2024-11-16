/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:19:16 by dagimeno          #+#    #+#             */
/*   Updated: 2024/02/02 17:22:22 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	j = 0;
	k = 0;
	if (!dst && !dstsize)
		return (ft_strlen(src));
	while (dst[i])
		i++;
	if (dstsize < i)
		k = i - dstsize;
	if (dstsize)
	{
		while (*src && j + i < dstsize - 1)
			dst[i + j++] = *src++;
		dst[i + j] = 0;
	}
	while (*src++)
		j++;
	return (i + j - k);
}
