# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 12:52:51 by tbourdea          #+#    #+#              #
#    Updated: 2023/04/21 14:41:48 by tbourdea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = fractol
SRC =	main.c \
		mandelbrot.c \
		ft_split.c \
		parsing.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
RM = rm -rf
HEADERS = -I ./include


all: ${NAME}
 
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -pg -o $(NAME)
	
debug: clean
	$(CC) $(SRC) $(LIBS) $(HEADERS) $(LFLAGS)  -g3 -O3 -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -I/usr/include -Imlx_linux -pg -O3 -c $< -o $@

clean:
	$(RM) ${OBJ}

fclean: clean
	$(RM) ${NAME}

re: fclean all


# NAME = fractol
# SRC = main.c
# OBJ = $(SRC:.c=.o)
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror
# LIB= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
# RM= rm -rf
# HEADERS= -I ./include

# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(CFLAGS) $(LIB) $(OBJ) -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) $(HEADERS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

# clean:
# 	$(RM) $(OBJ)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re