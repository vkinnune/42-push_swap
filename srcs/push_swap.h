/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:14:23 by vkinnune          #+#    #+#             */
/*   Updated: 2022/04/04 18:14:24 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 4096

enum	e_execs
{
	sa,
	sb,
	ss,
	pa,
	pb,
	ra,
	rb,
	rr,
	rra,
	rrb,
	rrr
};

typedef struct s_global {
	bool			verbose;
	bool			sleep;
	unsigned char	execs[20000];
	int				ec;
	int				a_stack[5000];
	int				b_stack[5000];
	int				a_stack_count;
	int				b_stack_count;
	int				sorted[5000];
	int				sorted_size;
}					t_global;

typedef struct s_chunk {
	int	high;
	int	low;
	int	size;
}	t_chunk;

/*
   Checker
   */

void	execute_instructions(t_global *g);
int		read_valid_input(t_global *g, char *memory_buffer);
void	flags(int *ac, char **av, t_global *g);
void	print_verbose(t_global *g, int exec_index);

/*
   Shared
   */

int		ft_out(char *reason);
int		isvalid(char buf[100], int i, t_global *g);
int		read_one_arg(char *p, t_global *g);
int		read_args(char **av, t_global *g);
void	bubblesort(int *newstack, int *oldstack, int count);
void	swap(int *a, int *b);
void	print(unsigned char *execs, int i);
void	execute(unsigned char type, t_global *g);
void	reformat(t_global *g);
int		is_stack_sorted(int *stack, int count);
int		is_chunk_sorted(t_chunk chunk, int count, t_global *g);
void	push_chunk(t_global *g);
void	make_chunk(t_global *g, t_chunk *chunk, int unsorted);
void	chunk_to_bottom(t_global *g, t_chunk *chunk, int unsorted);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_printf(const char *str, ...);
char	*ft_strncpy(char *dest, const char *src, size_t n);
void	check_for_duplicates(t_global g, int *memory_buffer);

/*
   Instructions
   */

void	swapa(t_global *g);
void	swapb(t_global *g);
void	pusha(t_global *g);
void	pushb(t_global *g);
void	rotatea(t_global *g);
void	rotateb(t_global *g);
void	rotaterotate(t_global *g);
void	reverserotatea(t_global *g);
void	reverserotateb(t_global *g);
void	reversereverse(t_global *g);
void	swapswap(t_global *g);

/*
   Push swap
   */

void	push_swap(t_global *g, int count);
int		get_rotate_amount(t_global *g, int b_num);
void	good_numbers_first(t_global *g);
int		get_closest_number(t_global *g, int b_num);
void	insert_to_a(t_chunk *chunk, t_global *g, int unsorted);
void	bruteforce(t_global *g, int count);
int		brute(int *type, int x, int *icount);
void	reset(t_global *g, int count, int *cpy);

typedef void		(*t_dis)(t_global *g);

static const t_dis	g_dispatcher[11] = {
	swapa,
	swapb,
	swapswap,
	pusha,
	pushb,
	rotatea,
	rotateb,
	rotaterotate,
	reverserotatea,
	reverserotateb,
	reversereverse
};

#endif
