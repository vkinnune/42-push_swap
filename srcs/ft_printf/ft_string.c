/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:25:58 by vkinnune          #+#    #+#             */
/*   Updated: 2022/02/08 12:27:37 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	character(t_info *var)
{
	char	c;
	char	str[2];

	c = va_arg(*(var->args), int);
	str[0] = c;
	str[1] = '\0';
	var->prec = -1;
	return (printstring(var, str, 1));
}

int	string(t_info *var)
{
	char	*str;

	str = va_arg(*(var->args), char *);
	if (!str && var->prec == -1)
	{
		var->size += write(1, "(null)", 6);
		return (1);
	}
	if (!(var->prec))
		str = 0;
	return (printstring(var, str, (int)ft_strlen(str)));
}

int	printstring(t_info *var, char *str, int len)
{
	if (var->prec > 0 && var->length > 0 && len > 0 && var->prec < len)
		var->length -= var->prec;
	else if (var->length > 0)
		var->length -= len;
	if (var->length > 0 && !(var->ladjust))
		while (--(var->length) >= 0)
			var->size += write(1, " ", 1);
	if (var->prec < len && var->prec > 0)
		var->size += write(1, str, var->prec);
	else
		var->size += write(1, str, len);
	if (var->length > 0 && var->ladjust)
		while (--(var->length) >= 0)
			var->size += write(1, " ", 1);
	return (1);
}
