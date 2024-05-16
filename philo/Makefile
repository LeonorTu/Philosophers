# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 11:18:34 by jtu               #+#    #+#              #
#    Updated: 2024/05/16 16:18:57 by jtu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c \
		ft_atoi.c \
		routine.c \
		monitor.c \
		utils.c

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

all: ${NAME}

${NAME}: ${SRCS}
	@cc $(CFLAGS) $^ -o $@
	@echo "---------Philosopher Ready---------"

clean:
	@rm -rf *.dSYM
	@rm -rf .vscode
	@rm -rf .DS_Store

fclean: clean
	@rm -f ${NAME}
	@echo "---------Everything Deleted---------"

re: fclean all

.PHONY: all clean fclean re