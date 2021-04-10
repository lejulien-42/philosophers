/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:58:52 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/10 17:41:58 by lejulien         ###   ########.fr       */
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
	take_fork(t_philo *phi, int index)
{
	phi->data->forks_status[index] = 0;
	pthread_mutex_lock(&phi->data->forks[index]);
	next_state(phi);
}

void
	ft_think(t_philo *phi)
{
	if (phi->state == THINK)
		display_state(phi);
	while (phi->state != EAT)
	{
		if (phi->state == DIED)
			return ;
		if (phi->id == 0)
		{
			if (phi->data->forks_status[phi->data->nbr - 1])
				take_fork(phi, phi->data->nbr - 1);
		}
		else
		{
			if (phi->data->forks_status[phi->id - 1])
				take_fork(phi, phi->id - 1);
		}
		if (phi->data->forks_status[phi->id])
			take_fork(phi, phi->id);
	}
}

void
	*philosopher(void *philos)
{
	t_philo	*phi;

	phi = (t_philo *)philos;
	phi->last_eat = 0;
	(phi->id % 2 == 0) ? (phi->state = SLEEP) : (phi->state = THINK);
	//while (!phi->data->started);
	while (phi->state != DIED && !phi->data->is_a_dead_guy)
	{
		(phi->state == THINK) ? ft_think(phi) : NULL;
		(phi->state == EAT) ? ft_eat(phi) : NULL;
		(phi->state == SLEEP) ? ft_sleep(phi) : NULL;
	}
	if (phi->state == DIED)
	{
		display_state(phi);
		phi->data->is_a_dead_guy = 1;
	}
	return (NULL);
}

static int
	check_death(t_philo *phi)
{
	if (phi->data->started && ft_get_ct(phi->data->c_time_start) - phi->last_eat > phi->data->time_to_die)
	{
		phi->state = DIED;
		return (1);
	}
	return (0);
}

void
	init_philos(t_philo **philos, struct timeval *c_time_start, int nbr)
{
	t_philo		*ptr;
	pthread_t	thread_id[nbr];
	int			i;

	ptr = *philos;
	i = 0;

	while (ptr)
	{
		pthread_create(&thread_id[i], NULL, philosopher, ptr);
		ptr = ptr->next;
		i++;
	}
	ptr = *philos;
	usleep(500);
	gettimeofday(ptr->data->c_time_start, NULL);
	ptr->data->started = 1;
	while (1)
	{
		if (check_death(ptr))
			break ;
		ptr = ptr->next;
		if (ptr == NULL)
			ptr = *philos;
	}
	ptr = *philos;
	i = 0;
	while (ptr)
	{
		pthread_join(thread_id[i], NULL);
		i++;
		ptr = ptr->next;
	}
}
