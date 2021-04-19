/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:32:58 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/19 15:54:42 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	ft_eat(void *ptr)
{
	t_philo *phi;

	phi = (t_philo *)ptr;
	display_state(phi);
	if (++phi->nbr_of_eats == phi->data->max_launch)
		sem_post(phi->data->phi_filled);
	if (phi->state == DIED)
		return ;
	phi->last_eat = ft_get_ct(&phi->start);
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

	phi = (t_philo *)ptr;
	display_state(phi);
	if (ft_usleep(phi->data->time_to_sleep, phi))
		return ;
	phi->state = THINK;
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
	if (!(phi->state == DIED))
		phi->state = EAT;
}
