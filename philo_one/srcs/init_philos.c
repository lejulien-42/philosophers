/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:58:52 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/05 17:22:24 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	ft_sleep(t_philo **philo)
{
	struct timeval	c_time_start;
	t_philo			*ptr;

	ptr = *philo;
	gettimeofday(&c_time_start, NULL);
	display_state(philo);
	while ((ft_get_ct(ptr->c_time_start) - ft_get_ct(&c_time_start)) < ptr->time_to_sleep)
	{
		if ((ft_get_ct(ptr->c_time_start) - ft_get_ct(ptr->c_time_last_eat)) >= ptr->time_to_die)
		{
			display_state(philo);
			ptr->state = DIED;
			return ;
		}
	}
	ptr->state = THINK;
}

void
	*philosopher(void *philo)
{
	t_philo	*ptr;

	ptr = *(t_philo **)philo;
	gettimeofday(ptr->c_time_last_eat, NULL);
	while (ptr->state != DIED)
	{
		if (ptr->state == SLEEP)
			ft_sleep(philo);
	}
	printf("->%d\n", ptr->state);
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
