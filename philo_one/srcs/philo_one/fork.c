/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:48:17 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/17 15:57:20 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	display_fork(t_philo *phi)
{
	if (!phi->data->is_dead)
	{
		pthread_mutex_lock(&phi->data->write_access);
		printf("%ld %d is taking a fork\n", ft_get_ct(&phi->start),
				phi->id + 1);
		pthread_mutex_unlock(&phi->data->write_access);
	}
}

static void
	take_l_fork(t_philo *phi)
{
	pthread_mutex_lock(phi->fork_l);
	display_fork(phi);
}

static void
	take_r_fork(t_philo *phi)
{
	pthread_mutex_lock(phi->fork_r);
	display_fork(phi);
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
