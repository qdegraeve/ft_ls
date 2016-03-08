# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 08:41:32 by qdegraev          #+#    #+#              #
#    Updated: 2016/03/08 02:10:06 by qdegraev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LIBPATH = ft_printf
LIB = $(LIBPATH)/libftprintf.a

NAME = ft_ls

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L ft_printf -lftprintf

SRC =  \
	./define_type.c \
	./ft_ls.c \
	./list_tools.c \
	./read_n_sort.c \
	./tools.c \
	./print.c \

OBJ = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(LIB):
	make -C $(LIBPATH)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBPATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBPATH)

re: fclean all

.PHONY: all re clean flcean

