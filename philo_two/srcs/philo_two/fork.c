/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:48:17 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/17 17:04:17 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	display_fork(t_philo *phi)
{
	if (!phi->data->is_dead)
	{
		printf("%ld %d is taking a fork\n", ft_get_ct(&phi->start),
				phi->id + 1);
	}
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
		ft_usleep(phi->data->time_to_die + 1, phi);
}
