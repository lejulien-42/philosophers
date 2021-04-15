/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:44:08 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/15 15:31:09 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	ft_eat(void *ptr)
{
	t_philo	*phi;

	phi = (t_philo *)ptr;
	display_state(phi);
	if (++phi->nbr_of_lunch == phi->data->max_launch)
		phi->data->phi_filled++;
	if (phi->state == DIED)
		return ;
	phi->last_eat = ft_get_ct(phi->data->c_time_start);
	if (ft_usleep(phi->data->time_to_eat, phi))
	{
		sem_post(phi->data->forks);
		return ;
	}
	sem_post(phi->data->forks);
	phi->state = SLEEP;
}

void
	ft_sleep(void *ptr)
{
	t_philo				*phi;
	unsigned long int	start;

	phi = (t_philo *)ptr;
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
	while (!phi->data->is_a_dead_guy &&
			ft_get_ct(phi->data->c_time_start) - now < time)
	{
		usleep(500);
		if (phi->state == DIED)
			return (1);
	}
	return (0);
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
