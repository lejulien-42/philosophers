# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejulien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/05 18:43:38 by lejulien          #+#    #+#              #
#    Updated: 2021/04/18 12:24:11 by lejulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILS = ./srcs/utils/ft_atoi.c ./srcs/utils/ft_itoa.c \
		./srcs/utils/ft_strcmp.c

SRCS = 	./srcs/philo_three/main.c ./srcs/philo_three/init_data.c \
		./srcs/philo_three/gen_philos.c ./srcs/philo_three/init_philos.c \
		./srcs/philo_three/time.c ./srcs/philo_three/display.c \
		./srcs/philo_three/eat.c ./srcs/philo_three/fork.c

SRCS_OBJS = ${SRCS:.c=.o}
UTILS_OBJS = ${UTILS:.c=.o}

FLAGS = -Wall -Wextra -Werror -lpthread -g3

.c.o:
	gcc -c $< -o $(<:.c=.o)

NAME = philo_three

$(NAME): $(SRCS_OBJS) $(UTILS_OBJS)
	gcc -o $(NAME) $(SRCS_OBJS) $(UTILS_OBJS) $(FLAGS)

clean:
	rm -f $(SRCS_OBJS) $(UTILS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re
