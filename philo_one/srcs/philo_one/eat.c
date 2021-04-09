/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:44:08 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/09 16:41:19 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	ft_eat(t_philo *phi)
{
	display_state(phi);
	phi->last_eat = ft_get_ct(phi->data->c_time_start);
	usleep(phi->data->time_to_eat * 1000);
	phi->state = SLEEP;
}

void
	ft_sleep(t_philo *phi)
{
	unsigned long int	start;

	display_state(phi);
	start = ft_get_ct(phi->data->c_time_start);
	while (ft_get_ct(phi->data->c_time_start) - start < phi->data->time_to_sleep)
	{
		if (ft_get_ct(phi->data->c_time_start) - phi->last_eat >= phi->data->time_to_die)
		{
			phi->state = DIED;
			return ;
		}
	}
	phi->state = THINK;
}
