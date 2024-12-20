# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 17:03:30 by lcollong          #+#    #+#              #
#    Updated: 2024/12/19 17:13:15 by lcollong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	~ Variables ~

NAME = pipex
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
SRCS = pipex.c
OBJ = ${SRCS:%.c=%.o}
LIBFT = libft
PRINTF = printf
LIBFT_LIB = ${LIBFT}/libft.a
PRINTF_LIB = ${PRINTF}/libftprintf.a

#	~ Regles ~

all : ${NAME}

${LIBFT_LIB} :
	@echo "\nCreating Libft...\n"
	make -C ${LIBFT}

${PRINTF_LIB} :
	@echo "\nCreating Printf library...\n"
	make -C ${PRINTF}

${NAME} : ${OBJ} ${LIBFT_LIB} ${PRINTF_LIB}
	${CC} ${OBJ} -L${LIBFT} -L${PRINTF} -lft -lftprintf -o ${NAME}

%.o : %.c
	${CC} ${CFLAGS} -I${LIBFT} -I${PRINTF} -c $< -o $@

clean :
	rm -f ${OBJ}
	make -C ${LIBFT} clean
	make -C ${PRINTF} clean

fclean : clean
	rm -f ${NAME}
	make -C ${LIBFT} fclean
	make -C ${PRINTF} fclean

re : fclean all

.PHONY : all clean fclean re
