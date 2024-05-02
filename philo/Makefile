# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 11:18:34 by jtu               #+#    #+#              #
#    Updated: 2024/05/02 13:41:34 by jtu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c \
		ft_atoi.c

CFLAGS = -Wall -Wextra -Werror -g

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