# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejulien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/05 18:43:38 by lejulien          #+#    #+#              #
#    Updated: 2021/04/03 15:47:23 by lejulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILS = ./utils/ft_atoi.c

SRCS = 	./srcs/main.c

SRCS_OBJS = ${SRCS:.c=.o}
UTILS_OBJS = ${UTILS:.c=.o}

FLAGS = -Wall -Wextra -Werror -lpthread

.c.o:
	gcc -c $< -o $(<:.c=.o)

NAME = philo_one

$(NAME): $(SRCS_OBJS) $(UTILS_OBJS)
	gcc $(FLAGS) -o $(NAME) $(SRCS_OBJS) $(UTILS_OBJS)

clean:
	rm -f $(SRCS_OBJS) $(UTILS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re
