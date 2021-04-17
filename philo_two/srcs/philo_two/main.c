/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:48:19 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/17 16:49:27 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int
	print_usage(void)
{
	write(2, "Usage : ./philo_one nbr_of_philos time_to_die time_", 51);
	write(2, "to_eat time_to_sleep [minimum_eat_for_each_philos]\n", 51);
	return (1);
}

static void
	free_data(t_data *data, char **av)
{
	sem_close(data->forks);
	sem_unlink("forks");
	sem_close(data->write_access);
	sem_unlink("write_access");
	free(data);
}

int
	main(int ac, char **av)
{
	t_philo	*philos;
	t_data	*data;

	philos = NULL;
	if (ac == 5 || ac == 6)
	{
		if (!(data = init_data(ac, av)))
			return (print_usage());
		if (!(philos = gen_philos(ac, av, data)))
		{
			free_data(data, av);
			return (print_usage());
		}
		init_philos(philos);
		free_data(data, av);
		free(philos);
	}
	else
		return (print_usage());
	return (0);
}
