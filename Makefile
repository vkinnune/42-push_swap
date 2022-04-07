NAME=checker
NAME2=push_swap
SRCS_CHECKER=srcs/checker.c
SRCS_SHARED=srcs/shared/shared_tools.c srcs/shared/shared_tools2.c srcs/shared/shared_ins.c srcs/shared/shared_ins2.c \
	    srcs/shared/shared_helpers.c srcs/shared/shared_helpers2.c
SRCS_PUSH_SWAP= srcs/push_swap.c srcs/bruteforce.c srcs/push_swap_main.c
OBJS_CHECKER=$(notdir $(SRCS_CHECKER:.c=.o))
OBJS_SHARED=$(notdir $(SRCS_SHARED:.c=.o))
OBJS_PUSH_SWAP=$(notdir $(SRCS_PUSH_SWAP:.c=.o))
FLAGS= -Wall -Wextra -Werror
RUN_LIB=make -C srcs/ft_printf fclean && make -C srcs/ft_printf
PRINTF=srcs/ft_printf/libftprintf.a
LIBFT=srcs/ft_printf/libft/libft.a

all: $(NAME) $(NAME2)

$(NAME):
	@$(RUN_LIB)
	gcc -v $(FLAGS) -c $(SRCS_CHECKER) $(SRCS_SHARED)
	gcc -v $(FLAGS) $(OBJS_CHECKER) $(OBJS_SHARED) $(PRINTF) $(LIBFT) $ -o $(NAME)

$(NAME2):
	@$(RUN_LIB)
	gcc -v $(FLAGS) -c $(SRCS_PUSH_SWAP) $(SRCS_SHARED)
	gcc -v $(FLAGS) $(OBJS_PUSH_SWAP) $(OBJS_SHARED) $(PRINTF) $(LIBFT) -o $(NAME2)

clean:
	rm -vf $(OBJS_CHECKER) $(OBJS_PUSH_SWAP) $(OBJS_SHARED)
	make -C srcs/ft_printf/ clean

fclean: clean
	rm -vf $(NAME) $(NAME2)
	make -C srcs/ft_printf/ fclean

re: fclean all
