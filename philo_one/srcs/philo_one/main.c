/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:42:30 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/16 16:20:14 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long int
	ft_get_ct(struct timeval *c_time_start)
{
	struct timeval	c_time_now;

	gettimeofday(&c_time_now, NULL);
	return (((c_time_now.tv_sec * 1000000 + c_time_now.tv_usec) -
			(c_time_start->tv_sec * 1000000 + c_time_start->tv_usec)) / 1000);
}

int
	free_philos(t_philo **philos)
{
	t_philo			*ptr;
	t_philo			*tmp;

	ptr = *philos;
	if (!*philos)
		return (1);
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	return (1);
}

static int
	print_usage(void)
{
	write(2, "Usage : ./philo_one nbr_of_philos time_to_die time_", 51);
	write(2, "to_eat time_to_sleep [minimum_eat_for_each_philos]\n", 51);
	return (1);
}

int
	main(int ac, char **av)
{
	t_philo			*philos;
	t_data			*data;
	struct timeval	c_time_start;

	philos = NULL;
	if (ac == 5 || ac == 6)
	{
		if (!(data = init_data(ac, av, &c_time_start)))
			return (print_usage());
		gen_philos(ac, av, &philos, data);
		if (philos == NULL)
			return (free_philos(&philos));
		init_philos(&philos, &c_time_start, ft_atoi(av[2]));
		free(data->forks);
		free(data);
		free_philos(&philos);
	}
	else
		return (print_usage());
	return (0);
}
