/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:51:05 by dagimeno          #+#    #+#             */
/*   Updated: 2024/04/23 22:19:28 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(char const *string, ...);
static int	parse_argument(va_list ap, char item);
static int	ft_putuns(unsigned int x, int cont);
static int	ft_puthex(unsigned int x, char item, int cont);
static int	ft_putptr(unsigned long x, int cont);

int	ft_printf(char const *string, ...)
{
	va_list	ap;
	int		i;
	int		cont;

	i = 0;
	cont = 0;
	va_start(ap, string);
	while (string[i])
	{
		if (string[i] == '%')
		{
			i++;
			cont += parse_argument(ap, string[i++]);
			if (cont < 0)
				return (-1);
			continue ;
		}
		if (write(1, &string[i++], 1) < 0)
			return (-1);
		cont++;
	}
	va_end(ap);
	return (cont);
}

static int	parse_argument(va_list ap, char item)
{
	int	cont;

	cont = 0;
	if (item == '%')
		cont += ft_putper();
	else if (item == 'c')
		cont += ft_putchar(va_arg(ap, int));
	else if (item == 's')
		cont += ft_putstr(va_arg(ap, char *));
	else if (item == 'p')
		cont += ft_putptr(va_arg(ap, unsigned long), 1);
	else if (item == 'i' || item == 'd')
		cont += ft_putnbr(va_arg(ap, int), 1);
	else if (item == 'u')
		cont += ft_putuns(va_arg(ap, unsigned int), 1);
	else if (item == 'x' || item == 'X')
		cont += ft_puthex(va_arg(ap, unsigned int), item, 1);
	return (cont);
}

static int	ft_putuns(unsigned int x, int cont)
{
	if (x > 9)
		cont = ft_putuns(x / 10, ++cont);
	if (cont < 0)
		return (0x80000000);
	x = x % 10 + 48;
	if (write(1, &x, 1) < 0)
		return (0x80000000);
	return (cont);
}

static int	ft_puthex(unsigned int x, char item, int cont)
{
	char			*hexa;
	unsigned int	aux;

	aux = x;
	hexa = "0123456789abcdef";
	if (item == 'X')
		hexa = "0123456789ABCDEF";
	if (aux >= 16)
	{
		aux /= 16;
		cont = ft_puthex(aux, item, ++cont);
	}
	if (cont < 0)
		return (0x80000000);
	aux = x % 16;
	if (write(1, &hexa[aux], 1) < 0)
		return (0x80000000);
	return (cont);
}

static int	ft_putptr(unsigned long x, int cont)
{
	char			*hexa;
	unsigned long	aux;

	if (cont == 1)
	{
		if (write(1, "0x", 2) < 0)
			return (0x80000000);
		cont += 2;
	}
	aux = x;
	hexa = "0123456789abcdef";
	if (aux >= 16)
	{
		aux /= 16;
		cont = ft_putptr(aux, ++cont);
	}
	if (cont < 0)
		return (0x80000000);
	aux = x % 16;
	if (write(1, &hexa[aux], 1) < 0)
		return (0x80000000);
	return (cont);
}
