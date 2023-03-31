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
# CFLAGS += -fsanitize=thread

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

# ./philo 1 800 200 200 mueren
# ./philo 5 800 200 200 viven
# ./philo 5 800 200 200 7 && ./philo 5 800 200 200 7 | grep "1 is eating" | wc -l viven
# ./philo 4 410 200 200 viven
# ./philo 4 310 200 100 mueren
# ./philo 3 310 103 103 viven
# ./philo 3 310 104 104 mueren

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