# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsid-ele <zsid-ele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 08:48:51 by zsid-ele          #+#    #+#              #
#    Updated: 2025/02/25 10:27:07 by zsid-ele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/allowed.c push_swap.c

CFLAGS = -Wall -Werror -Wextra

CC = cc

rm = rm -f

libft.d = libft/

printf.d = ft_printf/

printf = $(addprefix ${printf.d}, libftprintf.a)

libft = $(addprefix ${libft.d}, libft.a)

NAME = push_swap

all: $(NAME)

$(NAME): 	$(OBJ) $(libft) $(printf)
			@$(CC) $(CFLAGS) $(SRC) $(libft) $(printf) -o ${NAME}
			@echo "File is READY NAME of file: \033[0;32mpush_swap\033[0m"

$(libft): 
			@$(MAKE) -s -C $(libft.d)
$(printf):
			@$(MAKE) -s -C $(printf.d)
.c.o:
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
				@echo "Compiling $<."

cleandir:
		@cd libft && make -s fclean
		@cd ft_printf && make -s fclean

clean:	cleandir

fclean: clean 
		@$(rm) $(NAME)

re: fclean all

.PHONY: all clean fclean re cleandir .c.o 
