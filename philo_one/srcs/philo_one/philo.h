/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:44:58 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/07 20:56:29 by lejulien         ###   ########.fr       */
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

typedef struct			s_data
{
	int					nbr;
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
	int					max_launch;
	int					write_access_i;
	pthread_mutex_t		*write_access_m;
	pthread_mutex_t		*forks;
	struct timeval		*c_time_start;
}						t_data;

typedef struct			s_philo
{
	int					id;
	int					state;
	t_data				*data;
	unsigned long int	last_eat;
	int					nbr_of_lunch;
	struct s_philo		*next;
}						t_philo;

unsigned long int		ft_get_ct(struct timeval *c_time_start);
void					init_philos(t_philo **philos, struct timeval *c_time_start,  int nbr);
void					display_state(t_philo *phi);
#endif
