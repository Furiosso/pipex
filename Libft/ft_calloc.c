/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:53:49 by dagimeno          #+#    #+#             */
/*   Updated: 2024/02/01 14:31:52 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	if (((double) count > (double)((size_t) 0xffffffffffffffff) / size) ||
			(((double) size > (double)((size_t) 0xffffffffffffffff) / count)))
		return (NULL);
	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count * size)
		*((unsigned char *)ptr + i++) = 0;
	return ((void *)ptr);
}
