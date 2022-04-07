/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:26:07 by vkinnune          #+#    #+#             */
/*   Updated: 2022/02/08 12:27:06 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	mypow(long double x, long double y)
{
	long double	res;

	res = x;
	while (y > 1)
	{
		res = res * x;
		y--;
	}
	return (res);
}

int	decimal(t_info *var)
{
	char	buf[MAXBUF];
	char	*p;

	p = &buf[MAXBUF - 1];
	if (var->prec == -1)
		var->prec = 6;
	if (var->bytes == 64)
		p = ftoa(va_arg(*(var->args), long double), var, &buf[MAXBUF - 1]);
	else if (var->bytes == 32)
		p = ftoa(va_arg(*(var->args), double), var, &buf[MAXBUF - 1]);
	else
		p = ftoa(va_arg(*(var->args), double), var, &buf[MAXBUF - 1]);
	var->prec = -1;
	printnum(var, buf, p, (int)((&buf[MAXBUF - 1]) - p));
	return (1);
}

char	*dodecimal(long double n, t_info *var, char *p)
{
	long long unsigned int	nint;
	long double				nfloat;

	nint = (long long unsigned int)n;
	nfloat = n - (long double)nint;
	if (var->prec != 0)
	{
		nint = nfloat * mypow(10, var->prec);
		while (var->prec != 0)
		{
			*p-- = nint % 10 + '0';
			nint /= 10;
			(var->prec)--;
		}
		*p-- = '.';
	}
	return (p);
}

char	*ftoa(long double n, t_info *var, char *p)
{
	long long unsigned int	nint;
	int						minus;

	minus = 0;
	if (n < 0)
	{
		n = -n;
		minus = 1;
	}
	if (var->prec != 0)
		p = dodecimal(n, var, p);
	nint = (long long unsigned int)n;
	while (nint != 0)
	{
		*p-- = nint % 10 + '0';
		nint /= 10;
	}
	if (minus)
		*p-- = '-';
	return (p);
}
