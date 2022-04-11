/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:14:09 by vkinnune          #+#    #+#             */
/*   Updated: 2022/04/04 18:14:10 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
   g stands for global and stores all the relevant information our program needs
   like our stacks, counts and instructions we print out.

   Firstly we check if the data is in multiple arguments or one argument.
   Then we read byte by byte from standard input and check if we get a correct
   instruction followed by a new line.

   Our reformatting function makes it so our data goes from looking like:
   	Before	1 5 3 2
   	After	0 3 2 1
   We reformat so our data is easier to handle.

   Then we bubblesort our A stack and get the sorted and right answer.
   After that we execute our instructions we read from stdin and
   compare with ft_memcmp if our output is correct.
   */

int	main(int ac, char **av)
{
	char		memory[BUFF_SIZE * 4];
	t_global	g;

	ft_memset(&g, 0, sizeof(g));
	if (ac >= 2)
		flags(&ac, av, &g);
	if (ac >= 2)
	{
		if (!reading(ac, av, &g))
			ft_out("Error");
		reformat(&g);
		bubblesort((int *)memory, g.a_stack, g.a_stack_count);
		check_for_duplicates(g, (int *)memory);
		if (!read_valid_input(&g, memory))
			ft_out("Error");
		execute_instructions(&g);
		bubblesort((int *)memory, g.a_stack, g.a_stack_count);
		if (g.b_stack_count > 0)
			write(1, "KO\n", 3);
		if (ft_memcmp((int *)memory, g.a_stack, 4 * g.a_stack_count))
			write(1, "KO\n", 3);
		else
			write(1, "OK\n", 3);
	}
	return (0);
}

int	reading(int ac, char **av, t_global *g)
{
	if (ac == 2 && !read_one_arg(av[1 + g->verbose], g))
		return (0);
	else if (ac >= 3 && !read_args(av, g))
		return (0);
	return (1);
}

void	flags(int *ac, char **av, t_global *g)
{
	if (!ft_memcmp(av[1], "-vs", 3) || !ft_memcmp(av[1], "-sv", 3))
	{
		g->verbose = 1;
		*ac = *ac - 1;
		g->sleep = 1;
	}
	else if (!ft_memcmp(av[1], "-v", 2))
	{
		g->verbose = 1;
		*ac = *ac - 1;
	}
	else if (!ft_memcmp(av[1], "-h", 2))
	{
		ft_printf("Checker Usage:\n");
		ft_printf("Syntax: ./checker [-flags] .. [numbers] ..\n-v\t");
		ft_printf("Enables visualisation\n-s\tEnables slow mo\n-h\tShows usage\n");
		exit(0);
	}
}
/*
   Execute instructions read from stdin using a function pointer array
   */

void	execute_instructions(t_global *g)
{
	int	exec_index;

	exec_index = 0;
	if (g->verbose == 0)
		while (exec_index != g->ec)
			g_dispatcher[g->execs[exec_index++]](g);
}

/*
   Read the input one byte at a time
   */

int	read_valid_input(t_global *g, char *memory_buffer)
{
	int	instruction_count;
	int	byte_count;

	instruction_count = 0;
	byte_count = 0;
	while (read(0, memory_buffer + byte_count, 1) > 0)
	{
		if (isvalid(memory_buffer, instruction_count, g))
		{
			if (g->verbose == 1)
				print_verbose(g, instruction_count);
			instruction_count++;
			byte_count = 0;
			ft_memset(memory_buffer, 0, 100);
		}
		else if (memory_buffer[byte_count] == '\n')
			return (0);
		else
			byte_count++;
	}
	g->ec = instruction_count;
	return (1);
}
