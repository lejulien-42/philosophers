/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:44:58 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/04 16:11:33 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "../utils/utils.h"
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# define DIED	0
# define EAT	1
# define SLEEP	2
# define THINK	3
# define FORK	4

const char	*state[5] = {"has died", "is eating", "is sleeping", "is thinking",
						"has taken a fork"};

typedef struct			s_philo
{
	int					id;
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
	int					max_launch;
	struct timeval		*c_time_start;
	struct timeval		*c_time_last_eat;
	int					nbr_of_lunch;
	struct s_philo		*next;
}						t_philo;

unsigned long int		ft_get_ct(struct timeval *c_time_start);
#endif
