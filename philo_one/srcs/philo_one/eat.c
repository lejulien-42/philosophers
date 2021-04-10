/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:44:08 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/10 17:50:02 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	ft_eat(t_philo *phi)
{

	phi->last_eat = ft_get_ct(phi->data->c_time_start);
	display_state(phi);
	while (ft_get_ct(phi->data->c_time_start) - phi->last_eat < phi->data->time_to_eat)
	{
		if (phi->state == DIED)
			return ;
	}
	if (phi->id == 0)
	{
		phi->data->forks_status[phi->data->nbr - 1] = 1;
		pthread_mutex_unlock(&phi->data->forks[phi->data->nbr - 1]);
	}
	else
	{
		phi->data->forks_status[phi->id - 1] = 1;
		pthread_mutex_unlock(&phi->data->forks[phi->id - 1]);
	}
	phi->data->forks_status[phi->id] = 1;
	pthread_mutex_unlock(&phi->data->forks[phi->id]);
	phi->state = SLEEP;
}

void
	ft_sleep(t_philo *phi)
{
	unsigned long int	start;

	display_state(phi);
	start = ft_get_ct(phi->data->c_time_start);
	if (!phi->data->started)
	{
		phi->state = SLEEP;
		return ;
	}
	while (ft_get_ct(phi->data->c_time_start) - start < phi->data->time_to_sleep)
	{
		if (phi->state == DIED)
			return ;
	}
	phi->state = THINK;
}
