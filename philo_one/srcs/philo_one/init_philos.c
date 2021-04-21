/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:24:12 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/21 13:50:24 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	*philosopher(void *philos)
{
	t_philo	*phi;

	phi = (t_philo *)philos;
	phi->state = (phi->id % 2 == 0) ? SLEEP : THINK;
	usleep(500);
	while (!phi->data->is_dead && phi->state != DIED)
		phi->data->routine[phi->state](phi);
	if (phi->state == DIED)
	{
		display_state(phi);
		phi->data->is_dead = 1;
	}
	pthread_mutex_unlock(phi->fork_l);
	pthread_mutex_unlock(phi->fork_r);
	return (NULL);
}

static void
	check_death(t_philo *phi)
{
	int	i;

	i = 0;
	while (1)
	{
		if (ft_get_ct(&phi[i].start) - phi[i].last_eat > phi->data->time_to_die
			&& (phi[i].state != EAT || phi->data->time_to_die <
				phi->data->time_to_eat))
		{
			if (phi[i].state == THINK)
			{
				phi[i].state = DIED;
				display_state(&phi[i]);
				phi[i].state = THINK;
				phi->data->is_dead = 1;
			}
			else
				phi[i].state = DIED;
			break ;
		}
		if (phi->data->phi_filled == phi->data->nbr)
			phi->data->is_dead = 1;
		i++;
		if (i == phi->data->nbr)
			i = 0;
	}
}

void
	init_philos(t_philo *philos)
{
	int			i;
	pthread_t	origin[philos->data->nbr];

	i = -1;
	while (++i < philos->data->nbr)
	{
		gettimeofday(&philos[i].start, NULL);
		pthread_create(&origin[i], NULL, philosopher, &philos[i]);
	}
	usleep(2000);
	check_death(philos);
	i = -1;
	while (++i < philos->data->nbr)
		pthread_join(origin[i], NULL);
}
