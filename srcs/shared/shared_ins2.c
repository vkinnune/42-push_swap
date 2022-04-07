/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_ins2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:14:49 by vkinnune          #+#    #+#             */
/*   Updated: 2022/04/04 18:14:50 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rotateb(t_global *g)
{
	int	i;
	int	temp;

	i = 0;
	temp = g->b_stack[0];
	if (g->b_stack_count < 1)
		return ;
	while (i != g->b_stack_count)
	{
		g->b_stack[i] = g->b_stack[i + 1];
		g->b_stack[i + 1] = 0;
		i++;
	}
	g->b_stack[i - 1] = temp;
}

void	rotaterotate(t_global *g)
{
	rotatea(g);
	rotateb(g);
}

void	reverserotatea(t_global *g)
{
	int	i;
	int	temp;

	i = g->a_stack_count;
	temp = g->a_stack[i - 1];
	if (g->a_stack_count < 1)
		return ;
	g->a_stack[i - 1] = 0;
	while (i != 0)
	{
		g->a_stack[i] = g->a_stack[i - 1];
		i--;
	}
	g->a_stack[0] = temp;
}

void	reverserotateb(t_global *g)
{
	int	i;
	int	temp;

	i = g->b_stack_count;
	temp = g->b_stack[i - 1];
	if (g->b_stack_count < 1)
		return ;
	g->b_stack[i - 1] = 0;
	while (i != 0)
	{
		g->b_stack[i] = g->b_stack[i - 1];
		i--;
	}
	g->b_stack[0] = temp;
}
