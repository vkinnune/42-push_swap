/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:31:03 by vkinnune          #+#    #+#             */
/*   Updated: 2022/02/08 12:27:47 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printnum_more(t_info *var, int *n, char *p)
{
	if (var->sign)
		var->size += write (1, &(var->sign), 1);
	if (var->prefix)
		var->size += write (1, var->prefix, ft_strlen(var->prefix));
	if (var->padc == '0')
		*n = var->length;
	if (var->base == 8 && p[1] == '0' && var->alt)
		var->prec = 0;
}

int	printnum(t_info *var, char buf[MAXBUF], char *p, int len)
{
	int	n;

	n = var->prec - len;
	if (n > 0)
		var->length -= n;
	var->length -= len;
	if (var->sign)
		var->length--;
	if (var->prefix)
		var->length -= ft_strlen(var->prefix);
	if (var->length > 0 && !(var->ladjust) && var->padc == ' ')
		while (--(var->length) >= 0)
			var->size += write(1, " ", 1);
	printnum_more(var, &n, p);
	while (--n >= 0)
		var->size += write(1, "0", 1);
	if (var->prec != 0 || p[1] != '0')
		while (++p != &buf[MAXBUF])
			var->size += write (1, p, 1);
	else if (var->prec == 0 && p[1] == '0' && var->iswidth == TRUE)
		var->size += write (1, " ", 1);
	if (var->ladjust && var->length > 0)
		while (--(var->length) >= 0)
			var->size += write (1, " ", 1);
	return (1);
}

int	unsigned_int(t_info *var, char *ptr)
{
	init_unsigned(var, ptr);
	if (var->bytes == 64)
		return (donumber(var, va_arg(*(var->args), unsigned long long)));
	else if (var->bytes == 32)
		return (donumber(var, va_arg(*(var->args), unsigned long)));
	else if (var->bytes == 16)
		return (donumber(var, (unsigned short)va_arg(*(var->args),
					unsigned int)));
	else if (var->bytes == 8)
		return (donumber(var, (unsigned char)va_arg(*(var->args),
					unsigned int)));
	else if (sizeof(int) == sizeof(long) && var->bytes == 0)
		return (donumber(var, va_arg(*(var->args), unsigned long)));
	else if (sizeof(int) < sizeof(long) && var->bytes == 0)
		return (donumber(var, va_arg(*(var->args), unsigned int)));
	return (0);
}

void	init_unsigned(t_info *var, char *ptr)
{
	if (*ptr == 'o')
		var->base = 8;
	else if (*ptr == 'x' || *ptr == 'p')
	{
		var->base = 16;
	}
	else if (*ptr == 'X')
	{
		var->base = 16;
		var->capitals = 16;
	}
	if (*ptr == 'p')
	{
		var->alt = TRUE;
		var->bytes = 64;
	}
	if (var->sign == '+' || var->sign == ' ')
		var->sign = 0;
}

int	signed_int(t_info *var)
{
	signed long long	n;

	n = 0;
	if (var->bytes == 64)
		n = va_arg(*(var->args), long long);
	else if (var->bytes == 32)
		n = va_arg(*(var->args), long);
	else if (var->bytes == 16)
		n = (signed short)va_arg(*(var->args), int);
	else if (var->bytes == 8)
		n = (signed char)va_arg(*(var->args), int);
	else if (sizeof(int) == sizeof(long) && var->bytes == 0)
		n = va_arg(*(var->args), long);
	else if (sizeof(int) < sizeof(long) && var->bytes == 0)
		n = va_arg(*(var->args), int);
	if (n >= 0)
		return (donumber(var, (unsigned long long)n));
	var->sign = '-';
	return (donumber(var, (unsigned long long)-n));
}
