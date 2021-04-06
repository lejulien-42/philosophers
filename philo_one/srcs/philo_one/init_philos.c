/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:58:52 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/06 17:46:38 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	ft_sleep(t_philo **philo)
{
	struct timeval	c_time_start;
	t_philo			*ptr;
	unsigned long int	start_sleeping;

	ptr = *philo;
	gettimeofday(&c_time_start, NULL);
	start_sleeping = ft_get_ct(&c_time_start);
	display_state(philo);
	while ((ft_get_ct(ptr->data->c_time_start) - start_sleeping) < 11000)
		if ((ft_get_ct(ptr->data->c_time_start) - ptr->last_eat) >= ptr->data->time_to_die)
			return ((void)(ptr->state = DIED));
	ptr->state = THINK;
}

void
	*philosopher(void *philo)
{
	t_philo	*ptr;

	ptr = *(t_philo **)philo;
	ptr->last_eat = gettimeofday(ptr->data->c_time_start, NULL);
	while (ptr->state != DIED)
	{
		if (ptr->state == SLEEP)
			ft_sleep(philo);
	}
	display_state(philo);
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
	gettimeofday(c_time_start, NULL);
	while (ptr)
	{
		pthread_create(&thread_id[i], NULL, philosopher, (void *)&ptr);
		pthread_join(thread_id[i], NULL);
		ptr = ptr->next;
		i++;
	}
}
