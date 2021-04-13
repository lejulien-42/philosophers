/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:58:52 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/13 19:26:17 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int
	ft_check_death(t_philo *phi)
{
	if (ft_get_ct(phi->data->c_time_start) - phi->last_eat >= phi->data->time_to_die)
	{
		pthread_mutex_unlock(phi->fork_l);
		pthread_mutex_unlock(phi->fork_r);
		phi->state = DIED;
		return (1);
	}
	return (0);
}

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
	take_l_fork(t_philo *phi)
{
	pthread_mutex_lock(phi->fork_l);
	(phi->state == FORK) ? go_eat(phi) : go_fork(phi);
}

void
	take_r_fork(t_philo *phi)
{
	pthread_mutex_lock(phi->fork_r);
	(phi->state == FORK) ? go_eat(phi) : go_fork(phi);
}

void
	check_fork(t_philo *phi)
{
	if (ft_check_death(phi))
		return ;
	take_r_fork(phi);
	if (phi->data->nbr != 1)
	{
		if (ft_check_death(phi))
			return ;
		take_l_fork(phi);
	}
	else
		ft_usleep(phi->data->time_to_die + 1, phi);
}

void
	ft_think(void *ptr)
{
	t_philo *phi;

	phi = (t_philo *)ptr;
	display_state(phi);
	if (phi->state == DIED)
		return ;
	check_fork(phi);
}

void
	*philosopher(void *philos)
{
	t_philo	*phi;

	phi = (t_philo *)philos;
	phi->state = (phi->id % 2 == 0) ? SLEEP : THINK;
	while (!phi->data->started)
		phi->last_eat = 0;
	while (phi->state != DIED && !phi->data->is_a_dead_guy)
	{
		phi->data->routine[phi->state](phi);
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
	if (ft_get_ct(phi->data->c_time_start) - phi->last_eat >= phi->data->time_to_die)
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
	ft_usleep(500, ptr);
	gettimeofday(ptr->data->c_time_start, NULL);
	ptr->data->started = 1;
	while (!check_death(ptr))
	{
		ptr = ptr->next;
		(ptr == NULL) ? (ptr = *philos) : NULL;
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
