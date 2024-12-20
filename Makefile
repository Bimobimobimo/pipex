# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 17:03:30 by lcollong          #+#    #+#              #
#    Updated: 2024/12/20 17:56:17 by lcollong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	~ Variables ~

NAME = pipex
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
SRCS = pipex.c \
	parsing_fork.c \
	path_exec.c \
	last_cmd.c \
	utils.c

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


re : fclean all

.PHONY : all clean fclean re
