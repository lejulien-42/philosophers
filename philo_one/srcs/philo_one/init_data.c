/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:03:36 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/14 15:10:35 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	init_data_helper(t_data *data, int ac, char **av)
{
	data->routine[EAT] = ft_eat;
	data->routine[SLEEP] = ft_sleep;
	data->routine[THINK] = ft_think;
	data->phi_filled = 0;
	data->nbr = ft_atoi(av[1]);
	data->time_to_die = ft_atouli(av[2]);
	data->time_to_eat = ft_atouli(av[3]);
	data->time_to_sleep = ft_atouli(av[4]);
	data->nbr = ft_atoi(av[1]);
	if (ac == 6)
		data->max_launch = ft_atoi(av[5]);
	else
		data->max_launch = -1;
}

t_data
	*init_data(int ac, char **av, struct timeval *c_time_start)
{
	t_data	*data;
	int		i;

	i = 0;
	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
	if (!(data->forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t))))
		return (NULL);
	if (!(data->forks_status = malloc(ft_atoi(av[1]) * sizeof(int))))
		return (NULL);
	data->is_a_dead_guy = 0;
	data->started = 0;
	while (i < ft_atoi(av[1]))
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (NULL);
		data->forks_status[i] = 1;
		i++;
	}
	if (pthread_mutex_init(&data->data_access, NULL))
		return (NULL);
	init_data_helper(data, ac, av);
	data->c_time_start = c_time_start;
	return (data);
}