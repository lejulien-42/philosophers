/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:44:08 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/12 16:35:54 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	ft_r_fork(t_philo *phi)
{
	pthread_mutex_unlock(phi->fork_l);
	pthread_mutex_unlock(phi->fork_r);
	*phi->fork_l_i = 1;
	*phi->fork_r_i = 1;
}

void
	ft_eat(t_philo *phi)
{

	display_state(phi);
	phi->last_eat = ft_get_ct(phi->data->c_time_start);
	if (ft_usleep(phi->data->time_to_eat, phi))
		return ;
	ft_r_fork(phi);
	phi->state = SLEEP;
}

void
	ft_sleep(t_philo *phi)
{
	unsigned long int	start;

	display_state(phi);
	if (ft_usleep(phi->data->time_to_sleep, phi))
		return ;
	phi->state = THINK;
}

int
	ft_usleep(unsigned long int time, t_philo *phi)
{
	unsigned long int	now;

	now = ft_get_ct(phi->data->c_time_start);
	while (!phi->data->is_a_dead_guy && ft_get_ct(phi->data->c_time_start) - now < time)
	{
		usleep(100);
		if (phi->state == DIED)
			return (1);
	}
	return (0);
}
