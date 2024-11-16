/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:35:40 by dagimeno          #+#    #+#             */
/*   Updated: 2024/07/12 13:43:14 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_putnumber(char *number, long nb, int len);

char	*ft_itoa(int n)
{
	char	*number;
	long	nb;
	int		len;
	char	isnegative;

	nb = n;
	len = 1;
	isnegative = 0;
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	if (nb < 0)
	{
		len++;
		isnegative = 1;
	}
	number = malloc((len + 1) * sizeof(char));
	if (!number)
		return (NULL);
	if (isnegative)
		number[0] = '-';
	number[len] = 0;
	return (ft_putnumber(number, nb, len - 1));
}

static char	*ft_putnumber(char *number, long nb, int len)
{
	if (nb < 0)
		nb = -nb;
	if (nb > 9)
		ft_putnumber(number, nb / 10, len - 1);
	number[len] = nb % 10 + 48;
	return (number);
}
