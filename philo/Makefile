# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 21:56:41 by javmarti          #+#    #+#              #
#    Updated: 2023/01/17 21:56:41 by javmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCSDIR = ./srcs/
CFILES = philosophers.c input.c libft.c threads.c table.c

SRCS = ${addprefix ${SRCSDIR}, ${CFILES}}

OBJS = ${SRCS:.c=.o}

INC = -I ./includes/

NAME = philo

THREADFLAG = -pthread

RM = rm -rf
################################################################################
.PHONY: all test re fclean clean
################################################################################
all:		${NAME}

test:		${NAME}
		./${NAME} 2 10000 2000 2000

test1:		${NAME}
		./${NAME} 1 10000 2000 2000

testmeal:	${NAME}
		./${NAME} 2 10000 2000 2000 2

${NAME}:	${OBJS}
		@${CC} ${THREADFLAG} $^ -o ${NAME}

%.o:		%.c
		@${CC} -c ${CFLAGS} ${THREADFLAG} $^ -o $@ ${INC}

re:			fclean all

fclean:		clean
		@${RM} ${NAME}

clean:
		@${RM} ${OBJS}
################################################################################