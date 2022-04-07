/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:26:28 by vkinnune          #+#    #+#             */
/*   Updated: 2022/02/08 12:27:55 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	char	*ptr;
	va_list	args;
	t_info	var;
	int		size;

	va_start(args, str);
	var.args = &args;
	ptr = (char *)str;
	size = 0;
	while (*ptr != '\0')
	{
		if (*ptr != '%')
		{
			write(1, ptr, 1);
			ptr++;
			size++;
			continue ;
		}
		setdefaultvalues(&var);
		if (!init_print(&var, &ptr))
			return (-1);
		size += var.size;
	}
	va_end(args);
	return (size);
}

/*
   1. Check flags: Sets flags to  struct and returns
   	pointer when no more flags found
   2. Get width: Gets width or simply numbers and saves
   	them in the struct
   3. Get precision: Finds a dot then gets gets numbers
   	for precision. Also returns a pointer
   4. Do print: Does the print with given flags and options
   5. Get modifier: Gets either ll, hh, l or h
*/

int	init_print(t_info *var, char **ptr)
{
	char	*p;

	*ptr = check_flags(var, *ptr);
	*ptr = get_width(var, *ptr);
	*ptr = get_precision(var, *ptr);
	*ptr = get_modifier(var, *ptr);
	if (!doprint(var, *ptr))
	{
		p = ft_strchr(*ptr, '%');
		if (p)
		{
			printstring(var, "%", 1);
			*ptr = p + 1;
			return (1);
		}
		return (0);
	}
	*ptr += 1;
	return (1);
}

int	doprint(t_info *var, char *ptr)
{
	if (*ptr == 'd' || *ptr == 'i')
		return (signed_int(var));
	else if (*ptr == 'o' || *ptr == 'u' || *ptr == 'x'
		|| *ptr == 'X' || *ptr == 'p')
		return (unsigned_int(var, ptr));
	else if (*ptr == 'f')
		return (decimal(var));
	else if (*ptr == 'c')
		return (character(var));
	else if (*ptr == 's')
		return (string(var));
	return (0);
}

/*
   1. buf[MAXBUF]: build number there
   */
int	donumber(t_info *var, unsigned long long u)
{
	char	buf[MAXBUF];
	char	*p;
	char	digits[32];

	ft_strcpy(digits, "0123456789abcdef0123456789ABCDEF");
	p = &buf[MAXBUF - 1];
	if (var->alt)
		alt(var, u);
	*p-- = digits[(u % var->base) + var->capitals];
	u /= var->base;
	while (u != 0)
	{
		*p-- = digits[(u % var->base) + var->capitals];
		u /= var->base;
	}
	if (var->prec > 0)
		var->padc = ' ';
	return (printnum(var, buf, p, (int)((&buf[MAXBUF - 1]) - p)));
}

void	alt(t_info *var, unsigned long long u)
{
	if (var->base == 8 && var->alt)
	{
		var->prefix = "0";
		if (var->prec != 0)
			var->prec -= 1;
	}
	else if (var->base == 16 && var->capitals == 0 && u != 0)
		var->prefix = "0x";
	else if (var->base == 16 && var->capitals == 16 && u != 0)
		var->prefix = "0X";
}
