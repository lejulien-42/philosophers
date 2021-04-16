/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:48:17 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/16 17:52:45 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	check_fork(t_philo *phi)
{
	pthread_mutex_lock(phi->fork_r);
	pthread_mutex_lock(&phi->data->write_access);
	printf("fork fork\n");
	pthread_mutex_lock(&phi->data->write_access);
	pthread_mutex_lock(phi->fork_l);
	pthread_mutex_lock(&phi->data->write_access);
	printf("fork fork\n");
	pthread_mutex_lock(&phi->data->write_access);
}
