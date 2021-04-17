/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:32:58 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/17 16:54:13 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	ft_r_fork(t_philo *phi)
{
	sem_post(phi->data->forks);
}

void
	ft_eat(void *ptr)
{
	t_philo *phi;

	phi = (t_philo *)ptr;
	display_state(phi);
	if (++phi->nbr_of_eats == phi->data->max_launch)
		phi->data->phi_filled++;
	if (phi->state == DIED)
		return ;
	phi->last_eat = ft_get_ct(&phi->start);
	if (ft_usleep(phi->data->time_to_eat, phi))
	{
		ft_r_fork(phi);
		return ;
	}
	ft_r_fork(phi);
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
