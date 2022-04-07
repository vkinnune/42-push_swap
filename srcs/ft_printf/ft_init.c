/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:26:14 by vkinnune          #+#    #+#             */
/*   Updated: 2022/02/02 13:30:22 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*check_flags(t_info *var, char *ptr)
{
	char	c;

	ptr++;
	while (1)
	{
		c = *ptr;
		if (c == '#')
			var->alt = TRUE;
		else if (c == '-')
			var->ladjust = TRUE;
		else if (c == '+')
			var->sign = '+';
		else if (c == ' ')
		{
			if (var->sign == 0)
				var->sign = ' ';
		}
		else if (*ptr == '0' && var->ladjust == FALSE)
			var->padc = '0';
		else
			break ;
		ptr++;
	}
	return (ptr);
}

char	*get_width(t_info *var, char *ptr)
{
	char	c;

	c = *ptr;
	if (ft_isdigit(c))
	{
		while (ft_isdigit(c))
		{
			var->length = 10 * var->length + c - '0';
			c = *++ptr;
		}
		var->iswidth = TRUE;
	}
	return (ptr);
}

char	*get_precision(t_info *var, char *ptr)
{
	char	c;

	c = *ptr;
	if (c == '.')
	{
		c = *++ptr;
		if (ft_isdigit(c))
		{
			var->prec = 0;
			while (ft_isdigit(c))
			{
				var->prec = 10 * var->prec + c - '0';
				c = *++ptr;
			}
		}
		else
			var->prec = 0;
	}
	return (ptr);
}

char	*get_modifier(t_info *var, char *ptr)
{
	if (!ft_strncmp(ptr, "ll", 2) || !ft_strncmp(ptr, "hh", 2))
	{
		if (!ft_strncmp(ptr, "ll", 2))
			var->bytes = 64;
		else if (!ft_strncmp(ptr, "hh", 2))
			var->bytes = 8;
		return (ptr + 2);
	}
	if (*ptr == 'L')
		var->bytes = 64;
	else if (*ptr == 'l')
		var->bytes = 32;
	else if (*ptr == 'h')
		var->bytes = 16;
	else
		return (ptr);
	return (ptr + 1);
}

void	setdefaultvalues(t_info *var)
{
	var->alt = FALSE;
	var->ladjust = FALSE;
	var->blank = FALSE;
	var->issign = FALSE;
	var->sign = 0;
	var->padc = ' ';
	var->length = 0;
	var->prec = -1;
	var->bytes = 0;
	var->size = 0;
	var->base = 10;
	var->capitals = 0;
	var->prefix = 0;
	var->iswidth = FALSE;
}
