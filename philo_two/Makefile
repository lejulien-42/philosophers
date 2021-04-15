# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejulien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/05 18:43:38 by lejulien          #+#    #+#              #
#    Updated: 2021/04/15 15:17:04 by lejulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILS = ./srcs/utils/ft_atoi.c ./srcs/utils/ft_itoa.c \
		./srcs/utils/ft_strcmp.c

SRCS = 	./srcs/philo_two/main.c ./srcs/philo_two/init_philos.c \
		./srcs/philo_two/display.c ./srcs/philo_two/eat.c \
		./srcs/philo_two/forks.c ./srcs/philo_two/init_data.c \
		./srcs/philo_two/gen_philos.c

SRCS_OBJS = ${SRCS:.c=.o}
UTILS_OBJS = ${UTILS:.c=.o}

FLAGS = -Wall -Wextra -Werror -lpthread -g3

.c.o:
	gcc -c $< -o $(<:.c=.o)

NAME = philo_two

$(NAME): $(SRCS_OBJS) $(UTILS_OBJS)
	gcc -o $(NAME) $(SRCS_OBJS) $(UTILS_OBJS) $(FLAGS)

clean:
	rm -f $(SRCS_OBJS) $(UTILS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re
