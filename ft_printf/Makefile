# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 08:41:32 by qdegraev          #+#    #+#              #
#    Updated: 2016/03/11 16:26:56 by qdegraev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBPATH = libft
LIB = $(LIBPATH)/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L libft -lft

SRC = ft_printf.c \
	types.c \
	arg_length.c \
	flags.c \
	ft_putnbru.c \
	ft_utoa_base.c \
	type_d_i.c \
	type_s.c \
	type_x.c \
	type_percent.c \
	type_f.c \
	type_c.c \
	type_u.c \
	type_o.c \
	type_p.c \
	ft_wchar.c \

OBJ = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	ar rc temp.a $(OBJ)
	ranlib temp.a
	libtool -static -o $@ $(LIB) temp.a

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIB):
	make -C $(LIBPATH)

clean:
	make clean -C $(LIBPATH)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBPATH)
	rm -f $(NAME) temp.a

re: fclean all

.PHONY: all re clean flcean

