/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:58:10 by dagimeno          #+#    #+#             */
/*   Updated: 2024/02/02 16:56:58 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sbstr;
	size_t	cont;

	if (!s)
		return (NULL);
	cont = ft_strlen(s);
	if (cont <= start)
		return (ft_calloc(1, sizeof(char)));
	cont = 0;
	while (*(s + start + cont))
		cont++;
	if (cont < len)
		len = cont;
	len++;
	sbstr = malloc(sizeof(char) * len);
	if (!sbstr)
		return (NULL);
	cont = 0;
	while (cont < len - 1)
	{
		sbstr[cont] = *(s + start + cont);
		cont++;
	}
	sbstr[cont] = 0;
	return (sbstr);
}
