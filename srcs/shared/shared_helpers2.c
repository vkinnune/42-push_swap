/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:16:19 by vkinnune          #+#    #+#             */
/*   Updated: 2022/04/04 18:17:12 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
   make_chunk takes the unsorted list of numbers and
   takes its median and pushes all below the median
   to stack b to be sorted back to a.
*/

void	make_chunk(t_global *g, t_chunk *chunk, int unsorted)
{
	int	newstack[5000];
	int	median;
	int	i;

	bubblesort(newstack, g->a_stack, unsorted);
	median = newstack[unsorted / 2];
	chunk->low = newstack[0];
	chunk->high = median - 1;
	chunk->size = (newstack[median] - newstack[0]);
	i = 0;
	median /= 2;
	while (i != chunk->size)
	{
		if (g->a_stack[0] <= chunk->high && g->a_stack[0] >= chunk->low)
		{
			execute(pb, g);
			i++;
		}
		else if (g->b_stack[0] < median)
			execute(rr, g);
		else
			execute(ra, g);
	}
}

/*
   Push chunk to bottom
   */
void	chunk_to_bottom(t_global *g, t_chunk *chunk, int unsorted)
{
	int	i;

	i = 0;
	while (g->a_stack[i] != 0)
		i++;
	if (i == 0)
		i = chunk->size;
	else if ((i - (unsorted - chunk->size))
		> ((unsorted - chunk->size) - i))
		i = i - (unsorted - chunk->size);
	else
		i = (unsorted - chunk->size) - i;
	while (i > 0)
	{
		execute(ra, g);
		i--;
	}
}

char	*get_ins_str(unsigned char exec, char *str)
{
	if (exec == sa)
		ft_strncpy(str, "sa", 3);
	else if (exec == sb)
		ft_strncpy(str, "sb", 3);
	else if (exec == ss)
		ft_strncpy(str, "ss", 3);
	else if (exec == pa)
		ft_strncpy(str, "pa", 3);
	else if (exec == pb)
		ft_strncpy(str, "pb", 3);
	else if (exec == ra)
		ft_strncpy(str, "ra", 3);
	else if (exec == rb)
		ft_strncpy(str, "rb", 3);
	else if (exec == rr)
		ft_strncpy(str, "rr", 3);
	else if (exec == rra)
		ft_strncpy(str, "rra", 4);
	else if (exec == rrb)
		ft_strncpy(str, "rrb", 4);
	else if (exec == rrr)
		ft_strncpy(str, "rrr", 4);
	return (str);
}

void	print_verbose(t_global *g, int exec_index)
{
	int		i;
	char	str[10];

	if (g->sleep == true)
		sleep(1);
	g_dispatcher[g->execs[exec_index]](g);
	i = 0;
	write(1, "\033[0;33m", 8);
	if (g->a_stack_count != 0)
	{
		ft_printf("A_STACK:\t");
		while (i != g->a_stack_count)
			ft_printf("%d ", g->a_stack[i++]);
		ft_printf("\n");
	}
	i = 0;
	if (g->b_stack_count != 0)
	{
		ft_printf("B_STACK:\t");
		while (i != g->b_stack_count)
			ft_printf("%d ", g->b_stack[i++]);
		ft_printf("\n");
	}
	write(1, "\033[0;36m", 8);
	ft_printf("INSTRUCTION:\t%s\n\n", get_ins_str(g->execs[exec_index], str));
}

void	check_for_duplicates(t_global g, int *memory_buffer)
{
	int	i;

	i = 0;
	while (i != g.a_stack_count)
	{
		if (memory_buffer[i] != i)
			ft_out("Error");
		i++;
	}
}
