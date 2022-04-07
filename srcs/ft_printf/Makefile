LIBFT = ./libft/libft.a

NAME = libftprintf.a

SRCS = ft_printf.c ft_init.c ft_int.c ft_float.c ft_string.c

CC = gcc

FLAGS = -Wall -Wextra -Werror -c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	$(CC) $(FLAGS) $(SRCS)
	ar -rcs $(NAME) $(OBJS)

all : $(NAME)

clean :
	$(MAKE) clean -C ./libft
	rm -rf $(SURPL_O)
	rm -rf $(OBJS)

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re : fclean all
