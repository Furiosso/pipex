/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:38:09 by dagimeno          #+#    #+#             */
/*   Updated: 2024/02/02 14:54:24 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	totallen;

	if (!s1 || !s2)
		return (NULL);
	totallen = ft_strlen(s1) + ft_strlen(s2);
	totallen++;
	str = malloc(sizeof(char) * totallen);
	if (!str)
		return (NULL);
	totallen = 0;
	while (*s1)
		str[totallen++] = *s1++;
	while (*s2)
		str[totallen++] = *s2++;
	str[totallen] = 0;
	return (str);
}
