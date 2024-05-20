# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 11:18:34 by jtu               #+#    #+#              #
#    Updated: 2024/05/20 14:17:41 by jtu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = src/philo.c \
		src/ft_atoi.c \
		src/routine.c \
		src/monitor.c \
		src/utils.c \
		src/init.c \
		src/clean.c

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

OBJS = ${SRCS:.c=.o}

all: ${NAME}

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

${NAME}: ${OBJS}
	@cc $(CFLAGS) $^ -o $@
	@echo "---------Philosopher Ready---------"

clean:
	@rm -f ${OBJS}
	@rm -rf *.dSYM
	@rm -rf .vscode
	@rm -rf .DS_Store

fclean: clean
	@rm -f ${NAME}
	@echo "---------Everything Deleted---------"

re: fclean all

.PHONY: all clean fclean re