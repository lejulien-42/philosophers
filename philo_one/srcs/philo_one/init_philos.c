/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:58:52 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/14 16:29:14 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_unlock(phi->fork_l);
	pthread_mutex_unlock(phi->fork_r);
	return (NULL);
}

static void
	check_death(t_philo **philos)
{
	t_philo	*phi;

	phi = *philos;
	while (1)
	{
		if (ft_get_ct(phi->data->c_time_start) -
				phi->last_eat >= phi->data->time_to_die)
		{
			if (phi->state == THINK)
			{
				phi->state = DIED;
				display_state(phi);
				phi->state = THINK;
				phi->data->is_a_dead_guy = 1;
			}
			else
				phi->state = DIED;
			break ;
		}
		if (phi->data->phi_filled == phi->data->nbr)
			phi->data->is_a_dead_guy = 1;
		phi = phi->next;
		(phi == NULL) ? (phi = *philos) : NULL;
	}
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
	ft_usleep(1000, ptr);
	ptr->data->started = 1;
	gettimeofday(ptr->data->c_time_start, NULL);
	check_death(philos);
	ptr = *philos;
	i = 0;
	while (ptr)
	{
		pthread_join(thread_id[i], NULL);
		i++;
		ptr = ptr->next;
	}
}
