/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:14:15 by vkinnune          #+#    #+#             */
/*   Updated: 2022/04/04 18:18:13 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
   We have a while loop that stops when the numbers are sorted.
   */

void	push_swap(t_global *g, int count)
{
	t_chunk	chunks[50];
	int		unsorted;
	int		chunk_count;

	chunk_count = 0;
	unsorted = g->a_stack_count;
	while (!is_stack_sorted(g->a_stack, count))
	{
		if (unsorted == 1)
			execute(ra, g);
		make_chunk(g, &chunks[chunk_count], unsorted);
		while (!is_chunk_sorted(chunks[chunk_count], count, g))
			insert_to_a(&(chunks[chunk_count]), g, unsorted);
		unsorted -= chunks[chunk_count].size;
		chunk_count++;
	}
}
/*
   Most important optimization for me was calculating the amount of moves
   for every number pushing from B stack and to A stack with least
   amount of moves. Good numbers first does that.

   Then we get the rotate amount and decide if we should rotate or reverse rotate
   our way to our correct position.

   After we have rotated to a correct position we push our number to A stack
   */

void	insert_to_a(t_chunk *chunk, t_global *g, int unsorted)
{
	bool	reverse;
	int		rotate_amount;

	reverse = false;
	rotate_amount = 0;
	if (g->sorted_size)
	{
		good_numbers_first(g);
		rotate_amount = get_rotate_amount(g, g->b_stack[0]);
	}
	if ((g->a_stack_count - rotate_amount) < rotate_amount)
	{
		rotate_amount = g->a_stack_count - rotate_amount;
		reverse = true;
	}
	while (reverse == true && rotate_amount--)
		execute(rra, g);
	while (reverse == false && rotate_amount--)
		execute(ra, g);
	execute(pa, g);
	push_chunk(g);
	if (g->b_stack_count == 0)
		chunk_to_bottom(g, chunk, unsorted);
}

int	get_rotate_amount(t_global *g, int b_num)
{
	int	save_index;
	int	i;

	save_index = get_closest_number(g, b_num);
	i = 0;
	while (g->a_stack[i] != g->sorted[save_index])
		i++;
	if (g->sorted[save_index] < b_num)
		i++;
	else if ((g->a_stack_count - 1) == i && g->sorted[save_index] < b_num)
		i = 0;
	return (i);
}

void	good_numbers_first(t_global *g)
{
	int	a_rotate;
	int	b_rotate;
	int	save_index;

	b_rotate = 1;
	a_rotate = get_rotate_amount(g, g->b_stack[0]);
	save_index = 0;
	while (b_rotate != g->b_stack_count)
	{
		if (a_rotate > (get_rotate_amount(g, g->b_stack[b_rotate]) + b_rotate))
		{
			a_rotate = get_rotate_amount(g, g->b_stack[b_rotate]) + b_rotate;
			save_index = b_rotate;
		}
		b_rotate++;
	}
	a_rotate = get_rotate_amount(g, g->b_stack[save_index]);
	b_rotate = save_index;
	while (a_rotate-- > 0 && b_rotate-- > 0)
		execute(rr, g);
	while (b_rotate-- > 0)
		execute(rb, g);
}

int	get_closest_number(t_global *g, int b_num)
{
	int	save_index;
	int	save_distance;
	int	distance;
	int	i;

	i = 0;
	save_distance = INT_MAX;
	save_index = 0;
	while (i != g->sorted_size)
	{
		if (g->sorted[i] > b_num)
			distance = g->sorted[i] - b_num;
		else
			distance = b_num - g->sorted[i];
		if (distance < save_distance)
		{
			save_distance = distance;
			save_index = i;
		}
		i++;
	}
	return (save_index);
}
