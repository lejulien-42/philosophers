/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:44:08 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/08 15:59:28 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void
	ft_take_fork(t_philo *philo, int fork_index)
{
	philo->data->forks_status[fork_index] = 0;
	pthread_mutex_lock(&philo->data->forks[fork_index]);
	if (philo->state == THINK)
		philo->state = FORK;
	else
		philo->state = EAT;
	display_state(philo);
}

void
	ft_think(t_philo **ptr)
{
	t_philo	*philo;

	philo = *ptr;
	if (philo->state == THINK)
	{
		if (philo->id == 0)
		{
			if (philo->data->forks_status[philo->data->nbr - 1])
				return (ft_take_fork(philo, philo->data->nbr - 1));
		}
		else
		{
			if (philo->data->forks_status[philo->id - 1])
				return (ft_take_fork(philo, philo->id - 1));
		}
	}
	else
	{
		if (philo->data->forks_status[philo->id])
			return (ft_take_fork(philo, philo->id));
	}
	if ((ft_get_ct(philo->data->c_time_start) - philo->last_eat) >= philo->data->time_to_die)
		return ((void)(philo->state = DIED));
}

void
	ft_eat(t_philo **ptr)
{
	t_philo			*philo;
	struct timeval	c_ct;

	philo = *ptr;
	usleep(philo->data->time_to_eat * 1000);
	if (philo->id == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->data->nbr - 1]);
		philo->data->forks_status[philo->data->nbr - 1] = 1;
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		philo->data->forks_status[philo->id - 1] = 1;
	}
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	philo->data->forks_status[philo->id] = 1;
	philo->state = SLEEP;
	gettimeofday(&c_ct, NULL);
	philo->last_eat = ft_get_ct(&c_ct);
}
