/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:24:01 by dagimeno          #+#    #+#             */
/*   Updated: 2024/04/23 22:19:25 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putper(void);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n, int cont);

int	ft_putper(void)
{
	if (write(1, "%", 1) < 0)
		return (0x80000000);
	return (1);
}

int	ft_putchar(char c)
{
	if (write(1, &c, 1) < 0)
		return (0x80000000);
	return (1);
}

int	ft_putstr(char *s)
{
	int	cont;

	if (!s)
	{
		if (write (1, "(null)", 6) < 0)
			return (0x80000000);
		return (6);
	}
	cont = 0;
	while (*(s + cont))
		if (write(1, &s[cont++], 1) < 0)
			return (0x80000000);
	return (cont);
}

int	ft_putnbr(int n, int cont)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		if (write(1, "-", 1) < 0)
			return (0x80000000);
		cont++;
		nb = -nb;
	}
	if (nb > 9)
		cont = ft_putnbr(nb / 10, ++cont);
	if (cont < 0)
		return (0x80000000);
	nb = nb % 10 + 48;
	if (write(1, &nb, 1) < 0)
		return (0x80000000);
	return (cont);
}
