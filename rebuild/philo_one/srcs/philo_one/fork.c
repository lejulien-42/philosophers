/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:48:17 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/16 18:21:25 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	take_l_fork(t_philo *phi)
{
	pthread_mutex_lock(phi->fork_l);
	printf("fork fork\n");
}

void
	take_r_fork(t_philo *phi)
{
	pthread_mutex_lock(phi->fork_r);
	printf("fork fork\n");
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
