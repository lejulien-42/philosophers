/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:24:12 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/19 15:58:09 by lejulien         ###   ########.fr       */
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
	*check_death(void *ptr)
{
	t_philo *phi;

	phi = (t_philo *)ptr;
	while (1)
	{
		if (ft_get_ct(&phi->start) - phi->last_eat + 5 >
				phi->data->time_to_die + 4)
		{
			if (phi->state == THINK)
			{
				phi->state = DIED;
				display_state(phi);
				phi->state = THINK;
				phi->data->is_dead = 1;
			}
			else
				phi->state = DIED;
			return (NULL);
		}
	}
}

static void
	monitor_sim(pid_t *origin, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nbr)
	{
		sem_wait(philos->data->phi_filled);
		i++;
	}
	printf("--------------------------------------------------------------kill all\n");
}

void
	init_philos(t_philo *philos)
{
	int		i;
	pid_t		origin[philos->data->nbr];
	pthread_t	monitors[philos->data->nbr];

	i = -1;
	while (++i < philos->data->nbr)
	{
		if ((origin[i] = fork()) == 0)
		{
			gettimeofday(&philos[i].start, NULL);
			pthread_create(&monitors[i], NULL, check_death, &philos[i]);
			philosopher(&philos[i]);
			exit(0);
		}
	}
	usleep(500);
	monitor_sim(origin, philos);
}
