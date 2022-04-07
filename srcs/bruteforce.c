/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruteforce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:14:01 by vkinnune          #+#    #+#             */
/*   Updated: 2022/04/04 18:14:03 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reset(t_global *g, int count, int *cpy)
{
	ft_memcpy(g->a_stack, cpy, count * 4);
	ft_memset(g->b_stack, 0, count * 4);
	ft_memset(g->execs, 0, 10000);
	g->ec = 0;
	g->a_stack_count = count;
	g->b_stack_count = 0;
}

int	brute(int *type, int x, int *icount)
{
	if (type[x] >= 10)
	{
		if (x == 0)
			*icount += 1;
		type[x] = 0;
		return (0);
	}
	else if (type[x] != 10)
	{
		type[x]++;
		return (1);
	}
	return (0);
}

void	bruteforce(t_global *g, int count)
{
	int		type[5000];
	int		cpy[1000];
	int		i;
	int		icount;

	ft_memcpy(cpy, g->a_stack, count * 4);
	icount = 1;
	ft_memset(type, 0, 4 * 5000);
	while (!is_stack_sorted(g->a_stack, count))
	{
		reset(g, count, cpy);
		i = 0;
		while (i != icount)
			execute(type[i++], g);
		i = icount;
		while (i--)
			if (brute(type, i, &icount))
				break ;
	}
}
