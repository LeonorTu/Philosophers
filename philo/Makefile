# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 11:18:34 by jtu               #+#    #+#              #
#    Updated: 2024/05/17 20:41:03 by jtu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c \
		ft_atoi.c \
		routine.c \
		monitor.c \
		utils.c \
		init.c

CFLAGS = -Wall -Wextra -Werror

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