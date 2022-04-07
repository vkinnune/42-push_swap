/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:14:29 by vkinnune          #+#    #+#             */
/*   Updated: 2022/04/04 18:19:21 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	print(unsigned char *execs, int i)
{
	if (execs[i] == sa)
		ft_printf("sa\n");
	else if (execs[i] == sb)
		ft_printf("sb\n");
	else if (execs[i] == ss)
		ft_printf("ss\n");
	else if (execs[i] == pa)
		ft_printf("pa\n");
	else if (execs[i] == pb)
		ft_printf("pb\n");
	else if (execs[i] == ra)
		ft_printf("ra\n");
	else if (execs[i] == rb)
		ft_printf("rb\n");
	else if (execs[i] == rr)
		ft_printf("rr\n");
	else if (execs[i] == rra)
		ft_printf("rra\n");
	else if (execs[i] == rrb)
		ft_printf("rrb\n");
	else if (execs[i] == rrr)
		ft_printf("rrr\n");
}

void	execute(unsigned char type, t_global *g)
{
	g->execs[g->ec++] = type;
	g_dispatcher[type](g);
}

void	reformat(t_global *g)
{
	int	i;
	int	j;
	int	newstack[5000];

	i = 0;
	j = 0;
	bubblesort(newstack, g->a_stack, g->a_stack_count);
	while (i != g->a_stack_count)
	{
		while (newstack[j] != g->a_stack[i])
			j++;
		g->a_stack[i] = j;
		j = 0;
		i++;
	}
}

int	is_stack_sorted(int *stack, int count)
{
	int	i;

	i = 0;
	while (i != count)
	{
		if (stack[i] != i)
			return (0);
		i++;
	}
	return (1);
}
