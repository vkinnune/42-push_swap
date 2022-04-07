/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:17:44 by vkinnune          #+#    #+#             */
/*   Updated: 2022/04/04 18:17:57 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
   First we read arguments and then if we have 5 or less
   numbers we bruteforce the answer if there is 6 or more
   numbers we do our sorting
   */

int	main(int ac, char **av)
{
	t_global	g;
	int			i;
	int			memory[BUFF_SIZE];

	i = 0;
	ft_memset(&g, 0, sizeof(g));
	if (ac == 2)
	{
		if (!read_one_arg(av[1], &g))
			ft_out("Error");
	}
	else if (!read_args(av, &g))
		ft_out("Error");
	reformat(&g);
	bubblesort(memory, g.a_stack, g.a_stack_count);
	check_for_duplicates(g, memory);
	if (g.a_stack_count <= 5)
		bruteforce(&g, g.a_stack_count);
	else
		push_swap(&g, g.a_stack_count);
	while (i++ != (g.ec))
		print(g.execs, i - 1);
	return (0);
}
