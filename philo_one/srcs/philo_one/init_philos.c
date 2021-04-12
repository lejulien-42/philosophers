/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:58:52 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/12 17:03:27 by lejulien         ###   ########.fr       */
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
	take_l_fork(t_philo *phi)
{
	*phi->fork_l_i = 0;
	pthread_mutex_lock(phi->fork_l);
	(phi->state == FORK) ? go_eat(phi) : go_fork(phi);
}

void
	take_r_fork(t_philo *phi)
{
	*phi->fork_r_i = 0;
	pthread_mutex_lock(phi->fork_r);
	(phi->state == FORK) ? go_eat(phi) : go_fork(phi);
}

void
	check_fork(t_philo *phi)
{
	if (*phi->fork_l_i)
		take_l_fork(phi);
	else if (*phi->fork_r_i)
		take_r_fork(phi);
}

void
	ft_think(t_philo *phi)
{
	(phi->state == THINK) ? display_state(phi) : NULL;
	while (phi->state != EAT)
	{
		if (phi->state == DIED)
			return ;
		check_fork(phi);
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
		display_state(phi);
	return (NULL);
}

static int
	check_death(t_philo *phi)
{
	if (phi->data->started && ft_get_ct(phi->data->c_time_start) - phi->last_eat >= phi->data->time_to_die)
	{
		phi->state = DIED;
		phi->data->is_a_dead_guy = 1;
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
		gettimeofday(ptr->data->c_time_start, NULL);
		ptr->data->started = 1;
		pthread_create(&thread_id[i], NULL, philosopher, ptr);
		ptr = ptr->next;
		i++;
	}
	ptr = *philos;
	ft_usleep(500, ptr);
	while ("non")
	{
		if (check_death(ptr))
			break ;
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
