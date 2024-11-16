/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:39:11 by dagimeno          #+#    #+#             */
/*   Updated: 2024/01/22 17:01:18 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*needle;

	ch = c;
	needle = NULL;
	while (*s)
	{
		if (*s == ch)
			needle = (char *)s;
		s++;
	}
	if (*s == ch)
		return ((char *)s);
	return (needle);
}
