/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:48:17 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/21 15:55:35 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	display_fork(t_philo *phi)
{
	sem_wait(phi->data->write_access);
	if (!phi->data->is_dead)
		display_helper(ft_get_ct(&phi->start), phi->id + 1, "has taken a fork");
	sem_post(phi->data->write_access);
}


void
	check_fork(t_philo *phi)
{
	if (phi->data->nbr != 1)
	{
		sem_wait(phi->data->forks);
		display_fork(phi);
		display_fork(phi);
	}
	else
	{
		display_fork(phi);
		ft_usleep(phi->data->time_to_die, phi);
	}
}
