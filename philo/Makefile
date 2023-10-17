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

SRCSDIR = ./
CFILES = philosophers.c input.c libft.c threads.c table.c routine.c

SRCS = ${addprefix ${SRCSDIR}, ${CFILES}}

OBJS = ${SRCS:.c=.o}

INC = -I .

NAME = philo

THREADFLAG = -pthread

RM = rm -rf
################################################################################
.PHONY: all test re fclean clean
################################################################################
all:		${NAME}

error:		${NAME}
		./${NAME} 1 1 1 1 1 1 1
		./${NAME} 1 1 1
		./${NAME} 1 -1 1 1 1
		./${NAME} 1 ++1 1 1 1
		./${NAME} a 1 1 1 1
		./${NAME} 1 1 1 1 136213424523

${NAME}:	${OBJS}
		@${CC} ${CFLAGS} ${THREADFLAG} $^ -o ${NAME}

%.o:		%.c
		@${CC} -c ${CFLAGS} ${THREADFLAG} $^ -o $@ ${INC}

re:			fclean all

fclean:		clean
		@${RM} ${NAME}

clean:
		@${RM} ${OBJS}
################################################################################