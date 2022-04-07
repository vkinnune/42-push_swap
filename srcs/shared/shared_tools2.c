/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:15:04 by vkinnune          #+#    #+#             */
/*   Updated: 2022/04/04 18:15:05 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	reversereverse(t_global *g)
{
	reverserotatea(g);
	reverserotateb(g);
}

void	swapswap(t_global *g)
{
	swapa(g);
	swapb(g);
}

int	is_chunk_sorted(t_chunk chunk, int count, t_global *g)
{
	int	i;
	int	j;

	i = count - chunk.size;
	j = chunk.low;
	while (i != count)
	{
		if (g->a_stack[i] != j || i >= g->a_stack_count)
			return (0);
		i++;
		j++;
	}
	return (1);
}

void	push_chunk(t_global *g)
{
	g->sorted[g->sorted_size] = g->a_stack[0];
	g->sorted_size++;
}
