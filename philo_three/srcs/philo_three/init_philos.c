/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:24:12 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/21 17:21:07 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	*check_death(void *ptr)
{
	t_philo *phi;

	phi = (t_philo *)ptr;
	gettimeofday(&phi->start, NULL);
	phi->last_eat = ft_get_ct(&phi->start);
	while (!phi->data->is_dead)
	{
		usleep(1000);
		if (ft_get_ct(&phi->start) - phi->last_eat >
			phi->data->time_to_die && (phi->state != EAT ||
			phi->data->time_to_die < phi->data->time_to_eat))
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
	return (NULL);
}

static void
	*philosopher(void *philos)
{
	t_philo	*phi;
	pthread_t	monitors;
	int		i;

	phi = (t_philo *)philos;
	phi->state = (phi->id % 2 == 0) ? SLEEP : THINK;
	sem_wait(phi->data->start);
	pthread_create(&monitors, NULL, check_death, philos);
	gettimeofday(&phi->start, NULL);
	while (phi->state != DIED && !phi->data->is_dead)
		phi->data->routine[phi->state](phi);
	if (phi->state == DIED)
	{
		display_state(phi);
		phi->data->is_dead = 1;
	}
	sem_post(phi->data->forks);
	i = -1;
	while (++i < phi->data->nbr)
		sem_post(phi->data->phi_filled);
	return (NULL);
}

static void
	monitor_sim(pid_t *origin, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->data->nbr + 1)
		sem_post(philos->data->start);
	i = -1;
	while (++i < philos->data->nbr)
		sem_wait(philos->data->phi_filled);
	i = -1;
	while (++i < philos->data->nbr)
		kill(origin[i], SIGKILL);
}

void
	init_philos(t_philo *philos)
{
	int		i;
	pid_t		origin[philos->data->nbr];

	i = -1;
	while (++i < philos->data->nbr)
	{
		if ((origin[i] = fork()) == 0)
		{
			philosopher(&philos[i]);
			exit(0);
		}
	}
	usleep(1000);
	monitor_sim(origin, philos);
}
