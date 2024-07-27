/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:07:58 by dagimeno          #+#    #+#             */
/*   Updated: 2024/02/02 17:15:38 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	if (!haystack && !len)
		return (0);
	if (!*needle)
		return ((char *)haystack);
	j = 0;
	while (*haystack && j < len)
	{
		i = 0;
		k = j++;
		while (haystack[i] == needle[i] && haystack[i++] && k++ < len)
		{
			if (!needle[i])
				return ((char *)haystack);
		}
		haystack++;
	}
	return (0);
}
