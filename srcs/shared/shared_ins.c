/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_ins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:14:40 by vkinnune          #+#    #+#             */
/*   Updated: 2022/04/04 18:14:41 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swapa(t_global *g)
{
	int	temp;

	if (g->a_stack_count < 2)
		return ;
	temp = g->a_stack[0];
	g->a_stack[0] = g->a_stack[1];
	g->a_stack[1] = temp;
}

void	swapb(t_global *g)
{
	int	temp;

	if (g->b_stack_count < 2)
		return ;
	temp = g->b_stack[0];
	g->b_stack[0] = g->b_stack[1];
	g->b_stack[1] = temp;
}

void	pusha(t_global *g)
{
	int	i;

	i = g->a_stack_count;
	if (g->b_stack_count < 1)
		return ;
	while (i != 0)
	{
		g->a_stack[i] = g->a_stack[i - 1];
		i--;
	}
	g->a_stack[0] = g->b_stack[0];
	i = 0;
	while (i != g->b_stack_count)
	{
		g->b_stack[i] = g->b_stack[i + 1];
		g->b_stack[i + 1] = 0;
		i++;
	}
	g->b_stack_count--;
	g->a_stack_count++;
}

void	pushb(t_global *g)
{
	int	i;

	i = g->b_stack_count;
	if (g->a_stack_count < 1)
		return ;
	while (i != 0)
	{
		g->b_stack[i] = g->b_stack[i - 1];
		i--;
	}
	g->b_stack[0] = g->a_stack[0];
	i = 0;
	while (i != g->a_stack_count)
	{
		g->a_stack[i] = g->a_stack[i + 1];
		g->a_stack[i + 1] = 0;
		i++;
	}
	g->a_stack_count--;
	g->b_stack_count++;
}

void	rotatea(t_global *g)
{
	int	i;
	int	temp;

	i = 0;
	temp = g->a_stack[0];
	if (g->a_stack_count < 1)
		return ;
	while (i != g->a_stack_count)
	{
		g->a_stack[i] = g->a_stack[i + 1];
		g->a_stack[i + 1] = 0;
		i++;
	}
	g->a_stack[i - 1] = temp;
}
