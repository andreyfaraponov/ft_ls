# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/09 01:17:41 by afarapon          #+#    #+#              #
#    Updated: 2018/04/01 15:39:02 by afarapon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc -g

KEYS = -Wall -Wextra -Werror

IDIR = ./includes

LIBDIR = ./libft

LIBFT = $(LIBDIR)/libft.a

SRCDIR = srcs

SRC = \
	main.c \
	get_flags.c \
	service.c \
	print_info.c \
	engine_part_1.c \
	error_handle.c \
	print_directory.c \
	
_OBJ = $(SRC:%.c=%.o)

_DEPS = ft_ls.h

OBJ = $(SRC:.c=.o)

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

.PHONY: all, clean, fclean, re
.NOTPARALLEL:  all, clean, fclean, re
.SILENT:

all: $(NAME)

%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS) $(CFLAGS)

$(NAME): $(LIBFT) $(OBJ)
		cp libft/libft.a ./$(NAME)
		$(CC) -o $(NAME) $(OBJ) libft/libft.a -fsanitize=address

$(LIBFT):
	make -C $(LIBDIR)

clean:
	/bin/rm -rf *.o
	/bin/rm -rf libft/*.o

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -rf libft/libft.a

re: fclean all
