/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:44:58 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/14 14:48:39 by lejulien         ###   ########.fr       */
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
	int					phi_filled;
	pthread_mutex_t		*forks;
	pthread_mutex_t		data_access;
	int					*forks_status;
	int					is_a_dead_guy;
	int					started;
	struct timeval		*c_time_start;
	void				(*routine[5])(void *);
}						t_data;

typedef struct			s_philo
{
	int					id;
	int					state;
	t_data				*data;
	int					is_eating;
	unsigned long int	last_eat;
	int					*fork_l_i;
	int					*fork_r_i;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	int					nbr_of_lunch;
	struct timeval		*c_time_start;
	struct s_philo		*next;
}						t_philo;

unsigned long int		ft_get_ct(struct timeval *c_time_start);
void					init_philos(t_philo **philos,
						struct timeval *c_time_start, int nbr);
void					display_state(t_philo *phi);
void					ft_eat(void *phi);
void					ft_sleep(void *phi);
int						ft_usleep(unsigned long int time, t_philo *phi);
void					ft_think(void *phi);
void					check_fork(t_philo *phi);
#endif
