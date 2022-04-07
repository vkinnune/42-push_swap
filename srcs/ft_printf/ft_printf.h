/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:26:37 by vkinnune          #+#    #+#             */
/*   Updated: 2022/02/08 12:27:31 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdbool.h>

# define FALSE 0
# define TRUE 1
# define MAXBUF 64

typedef struct s_info
{
	bool	alt;
	bool	ladjust;
	bool	blank;
	bool	issign;
	bool	iswidth;
	char	sign;
	char	padc;
	va_list	*args;
	int		length;
	int		prec;
	int		bytes;
	int		base;
	int		capitals;
	int		size;
	char	*prefix;
}	t_info;

int			signed_int(t_info *var);
int			donumber(t_info *var, unsigned long long u);
int			ft_printf(const char *str, ...);
int			doprint(t_info *var, char *ptr);
int			init_print(t_info *var, char **ptr);
int			unsigned_int(t_info *var, char *ptr);
int			decimal(t_info *var);
int			character(t_info *var);
int			string(t_info *var);
char		*check_flags(t_info *var, char *ptr);
char		*get_width(t_info *var, char *ptr);
char		*get_precision(t_info *var, char *ptr);
char		*get_modifier(t_info *var, char *ptr);
void		setdefaultvalues(t_info *var);
void		init_unsigned(t_info *var, char *ptr);
char		*ftoa(long double n, t_info *var, char *p);
long double	mypow(long double x, long double y);
int			printstring(t_info *var, char *str, int len);
int			printnum(t_info *var, char buf[MAXBUF], char *p, int len);
void		alt(t_info *var, unsigned long long u);
char		*dodecimal(long double n, t_info *var, char *p);
#endif
