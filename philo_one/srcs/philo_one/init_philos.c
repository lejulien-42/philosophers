/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:58:52 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/11 17:37:11 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void
	go_eat(t_philo *phi)
{
	display_state(phi);
	phi->state = EAT;
}

static void
	go_fork(t_philo *phi)
{
	phi->state = FORK;
	display_state(phi);
}

void
	take_fork(t_philo *phi, int index)
{
	phi->data->forks_status[index] = 0;
	pthread_mutex_lock(&phi->data->forks[index]);
	(phi->state == FORK) ? go_eat(phi) : go_fork(phi);
}

void
	first(t_philo *phi)
{
	if (phi->data->forks_status[phi->data->nbr - 1])
		take_fork(phi, phi->data->nbr - 1);
	if (phi->data->forks_status[phi->id])
		take_fork(phi, phi->id);
}

void
	others(t_philo *phi)
{
	if (phi->data->forks_status[phi->id - 1])
		take_fork(phi, phi->id - 1);
	if (phi->data->forks_status[phi->id])
		take_fork(phi, phi->id);
}

void
	ft_think(t_philo *phi)
{
	(phi->state == THINK) ? display_state(phi) : NULL;
	while (phi->state != EAT)
	{
		if (phi->state == DIED)
			return ;
		(phi->id == 0) ? first(phi) : others(phi);
	}
}

void
	*philosopher(void *philos)
{
	t_philo	*phi;

	phi = (t_philo *)philos;
	(phi->id % 2 == 0) ? (phi->state = SLEEP) : (phi->state = THINK);
	while (!phi->data->started)
		phi->last_eat = 0;
	while (phi->state != DIED && !phi->data->is_a_dead_guy)
	{
		if (phi->state == THINK)
			ft_think(phi);
		if (phi->state == EAT)
			ft_eat(phi);
		if (phi->state == SLEEP)
			ft_sleep(phi);
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
		return ((int)(phi->state = DIED) + 1);
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
	usleep(510);
	gettimeofday(ptr->data->c_time_start, NULL);
	ptr->data->started = 1;
	gettimeofday(ptr->data->c_time_start, NULL);
	while ("non")
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
