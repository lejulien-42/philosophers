/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:58:52 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/08 17:22:37 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	ft_sleep(t_philo **philo)
{
	struct timeval	c_time_start;
	unsigned long int	start_sleeping;
	t_philo				*ptr;

	ptr = *philo;
	gettimeofday(&c_time_start, NULL);
	start_sleeping = ft_get_ct(&c_time_start);
	display_state(ptr);
	while ((ft_get_ct(ptr->data->c_time_start) - start_sleeping) < ptr->data->time_to_sleep)
		if ((ft_get_ct(ptr->data->c_time_start) - ptr->last_eat) >= ptr->data->time_to_die)
			return ((void)(ptr->state = DIED));
	ptr->state = THINK;
}

void
	*philosopher(void *philo)
{
	t_philo	*ptr;

	ptr = (t_philo *)philo;
	if (ptr->id % 2 == 0)
		ptr->state = THINK;
	ptr->last_eat = 0;
	while (ptr->state != DIED && !ptr->data->is_a_dead_guy[0])
	{
		if (ptr->state == SLEEP)
			ft_sleep(&ptr);
		if (ptr->state == THINK || ptr->state == FORK)
			ft_think(&ptr);
		if (ptr->state == EAT)
			ft_eat(&ptr);
	}
	ptr->data->is_a_dead_guy[0] = 1;
	display_state(ptr);
	ptr->data->write_access_i[0] = 0;
	pthread_mutex_lock(ptr->data->write_access_m);
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

	philos[0]->data->write_access_i[0] = 1;
	gettimeofday(c_time_start, NULL);
	while (ptr)
	{
		pthread_create(&thread_id[i], NULL, philosopher, ptr);
		ptr = ptr->next;
		i++;
	}
	ptr = *philos;
	i = 0;
	while (ptr)
	{
		pthread_join(thread_id[i], NULL);
		ptr = ptr->next;
		i++;
	}
}
