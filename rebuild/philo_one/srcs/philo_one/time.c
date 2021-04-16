/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:42:27 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/16 17:40:33 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long int
	ft_get_ct(struct timeval *start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((now.tv_sec * 1000000 + now.tv_usec) -
			(start->tv_sec * 1000000 + start->tv_usec)) / 1000);
}

int
	ft_usleep(unsigned long int time, t_philo * phi)
{
	unsigned long int	now;

	now = ft_get_ct(&phi->start);
	while (!phi->data->is_dead && ft_get_ct(&phi->start) - now < time)
	{
		usleep(500);
		if (phi->state == DIED)
			return (1);
	}
	return (0);
}
