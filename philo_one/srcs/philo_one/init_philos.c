/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:58:52 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/09 16:47:38 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void
	next_state(t_philo *phi)
{
	if (phi->state == FORK)
	{
		display_state(phi);
		phi->state = EAT;
	}
	else if (phi->state == THINK)
	{
		phi->state = FORK;
		display_state(phi);
	}
}

void
	ft_think(t_philo *phi)
{
	if (phi->state == THINK)
		display_state(phi);
	while (phi->state != EAT)
	{
		if (ft_get_ct(phi->data->c_time_start) - phi->last_eat >= phi->data->time_to_die)
		{
			phi->state = DIED;
			return ;
		}
		if (phi->id == 0)
		{
			if (phi->data->forks_status[phi->data->nbr - 1])
			{
				phi->data->forks_status[phi->data->nbr - 1] = 0;
				pthread_mutex_lock(&phi->data->forks[phi->data->nbr - 1]);
				next_state(phi);
			}
		}
		else
		{
			if (phi->data->forks_status[phi->id - 1])
			{
				phi->data->forks_status[phi->id - 1] = 0;
				pthread_mutex_lock(&phi->data->forks[phi->id - 1]);
				next_state(phi);
			}
		}
		if (phi->data->forks_status[phi->id])
		{
			phi->data->forks_status[phi->id] = 0;
			pthread_mutex_lock(&phi->data->forks[phi->id]);
			next_state(phi);
		}
	}
}

void
	*philosopher(void *philos)
{
	t_philo	*phi;

	phi = (t_philo *)philos;
	phi->last_eat = 0;
	if (phi->id % 2 == 0)
		phi->state = THINK;
	while (!phi->data->started);
	while (phi->state != DIED && !phi->data->is_a_dead_guy)
	{
		if (phi->state == THINK)
			ft_think(phi);
		else if (phi->state == EAT)
			ft_eat(phi);
		else if (phi->state == SLEEP)
			ft_sleep(phi);
	}
	if (phi->state == DIED)
	{
		display_state(phi);
		phi->data->is_a_dead_guy = 1;
	}
	return (NULL);
}

void
	init_philos(t_philo **philos, struct timeval *c_time_start, int nbr)
{
	t_philo		*ptr;
	pthread_t	thread_id[nbr];
	int			i;

	ptr = *philos;
	i = 0;

	gettimeofday(ptr->data->c_time_start, NULL);
	while (ptr)
	{
		pthread_create(&thread_id[i], NULL, philosopher, ptr);
		ptr = ptr->next;
		i++;
	}
	usleep(10000);
	ptr = *philos;
	gettimeofday(ptr->data->c_time_start, NULL);
	ptr->data->started = 1;
	ptr = *philos;
	i = 0;
	while (ptr)
	{
		pthread_join(thread_id[i], NULL);
		i++;
		ptr = ptr->next;
	}
}
