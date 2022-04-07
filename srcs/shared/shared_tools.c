/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:14:59 by vkinnune          #+#    #+#             */
/*   Updated: 2022/04/04 18:15:00 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_out(char *reason)
{
	char	*p;

	p = reason;
	while (*p)
	{
		write(2, p, 1);
		p++;
	}
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int	isvalid(char buf[100], int i, t_global *g)
{
	if (!ft_memcmp(buf, "sa\n", 3))
		g->execs[i] = sa;
	else if (!ft_memcmp(buf, "sb\n", 3))
		g->execs[i] = sb;
	else if (!ft_memcmp(buf, "ss\n", 3))
		g->execs[i] = ss;
	else if (!ft_memcmp(buf, "pa\n", 3))
		g->execs[i] = pa;
	else if (!ft_memcmp(buf, "pb\n", 3))
		g->execs[i] = pb;
	else if (!ft_memcmp(buf, "ra\n", 3))
		g->execs[i] = ra;
	else if (!ft_memcmp(buf, "rb\n", 3))
		g->execs[i] = rb;
	else if (!ft_memcmp(buf, "rr\n", 3))
		g->execs[i] = rr;
	else if (!ft_memcmp(buf, "rra\n", 4))
		g->execs[i] = rra;
	else if (!ft_memcmp(buf, "rrb\n", 4))
		g->execs[i] = rrb;
	else if (!ft_memcmp(buf, "rrr\n", 4))
		g->execs[i] = rrr;
	else
		return (0);
	return (1);
}

int	read_one_arg(char *p, t_global *g)
{
	long int	number;

	number = 0;
	while (*p != 0)
	{
		if (*p >= '0' && *p <= '9')
		{
			number *= 10;
			number += *p++ - '0';
		}
		else if (*p == ' ')
		{
			if (number > INT_MAX)
				return (0);
			g->a_stack[g->a_stack_count++] = number;
			number = 0;
			p++;
		}
		else
			return (0);
	}
	if (number > INT_MAX)
		return (0);
	g->a_stack[g->a_stack_count++] = number;
	return (1);
}

int	read_args(char **av, t_global *g)
{
	long int	number;
	char		*p;

	number = 0;
	g->a_stack_count = 0;
	p = av[(g->a_stack_count + 1) + g->verbose];
	while (av[(g->a_stack_count + 1) + g->verbose] != 0)
	{
		if (*p >= '0' && *p <= '9')
		{
			number *= 10;
			number += *p++ - '0';
			if (*p == 0)
			{
				if (number > INT_MAX)
					return (0);
				g->a_stack[g->a_stack_count++] = number;
				p = av[(g->a_stack_count + 1) + g->verbose];
				number = 0;
			}
		}
		else
			return (0);
	}
	return (1);
}

void	bubblesort(int *newstack, int *oldstack, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (count <= 1)
	{
		newstack[0] = oldstack[0];
		return ;
	}
	ft_memcpy(newstack, oldstack, count * 4);
	while (i != count)
	{
		if (newstack[j] > newstack[j + 1])
			swap(&newstack[j], &newstack[j + 1]);
		j++;
		if (j == count - 1)
		{
			j = 0;
			i++;
		}
	}
}
