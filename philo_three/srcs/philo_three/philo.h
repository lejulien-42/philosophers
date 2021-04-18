/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:48:57 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/17 16:51:58 by lejulien         ###   ########.fr       */
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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# define EAT	0
# define SLEEP	1
# define THINK	2
# define DIED	3

typedef struct			s_data
{
	int					nbr;
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
	int					max_launch;
	int					phi_filled;
	sem_t				*forks;
	sem_t				*write_access;
	int					is_dead;
	void				(*routine[4])(void *);
}						t_data;

typedef struct			s_philo
{
	int					id;
	int					state;
	struct timeval		start;
	t_data				*data;
	int					nbr_of_eats;
	unsigned long int	last_eat;
}						t_philo;

t_data					*init_data(int ac, char **av);
t_philo					*gen_philos(int ac, char **av, t_data *data);
unsigned long int		ft_get_ct(struct timeval *start);
void					init_philos(t_philo *philos);
void					display_state(t_philo *ptr);
int						ft_usleep(unsigned long int time, t_philo *phi);
void					ft_eat(void *ptr);
void					ft_sleep(void *ptr);
void					ft_think(void *ptr);
void					check_fork(t_philo *phi);
#endif
