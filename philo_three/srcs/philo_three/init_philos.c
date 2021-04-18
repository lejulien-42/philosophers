/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:24:12 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/18 16:52:22 by lejulien         ###   ########.fr       */
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
	sem_post(phi->data->forks);
	return (NULL);
}

static void
	check_death(t_philo *phi)
{
	int	i;

	i = 0;
	while (1)
	{
		if (ft_get_ct(&phi[i].start) - phi[i].last_eat + 5 >
			phi->data->time_to_die + 4)
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
	int		i;
	pid_t	origin[philos->data->nbr];

	i = -1;
	while (++i < philos->data->nbr)
	{
		if ((origin[i] = fork()) == 0)
		{
			gettimeofday(&philos[i].start, NULL);
			philosopher(&philos[i]);
			exit(0);
		}
	}
	usleep(2000);
	check_death(philos);
	i = -1;
}
