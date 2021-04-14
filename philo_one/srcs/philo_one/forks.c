/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:31:26 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/14 14:47:42 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	go_eat(t_philo *phi)
{
	display_state(phi);
	phi->state = EAT;
}

static void
	go_fork(t_philo *phi)
{
	phi->state = FORK;
	display_state(phi);
}

void
	take_l_fork(t_philo *phi)
{
	pthread_mutex_lock(phi->fork_l);
	(phi->state == FORK) ? go_eat(phi) : go_fork(phi);
}

void
	take_r_fork(t_philo *phi)
{
	pthread_mutex_lock(phi->fork_r);
	(phi->state == FORK) ? go_eat(phi) : go_fork(phi);
}

void
	check_fork(t_philo *phi)
{
	take_r_fork(phi);
	if (phi->data->nbr != 1)
		take_l_fork(phi);
	else
		ft_usleep(phi->data->time_to_die + 1, phi);
}
