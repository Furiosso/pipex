/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:05:31 by dagimeno          #+#    #+#             */
/*   Updated: 2024/01/22 16:56:02 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dst_chr;
	const unsigned char	*src_chr;

	i = 0;
	dst_chr = (unsigned char *)dst;
	src_chr = (const unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	while (i < len)
	{
		if ((src_chr + i++) == dst_chr)
		{
			while (len--)
				dst_chr[len] = src_chr[len];
			*dst_chr = *src_chr;
			return ((void *)dst);
		}
	}
	i = 0;
	while (len--)
		dst_chr[i++] = *src_chr++;
	return ((void *)dst);
}
