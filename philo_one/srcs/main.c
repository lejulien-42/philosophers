/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:42:30 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/05 17:22:26 by lejulien         ###   ########.fr       */
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

void
	gen_philos(int ac, char **av, t_philo **philos, struct timeval *c_time_start)
{
	int		i;
	t_philo	*phi;
	t_philo	*ptr;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		ptr = *philos;
		if (!(phi = malloc(sizeof(t_philo))))
			return ;
		phi->id = i;
		phi->state = SLEEP;
		phi->time_to_die = ft_atouli(av[2]);
		phi->time_to_die = ft_atouli(av[3]);
		phi->time_to_die = ft_atouli(av[4]);
		phi->c_time_start = c_time_start;
		phi->c_time_last_eat = NULL;
		phi->nbr_of_lunch = 0;
		phi->next = NULL;
		if (ac == 6)
			phi->max_launch = ft_atoi(av[5]);
		else
			phi->max_launch = -1;
		if (!*philos)
			*philos = phi;
		else
		{
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = phi;
		}
		i++;
	}
}

int
	free_philos(t_philo **philos)
{
	t_philo	*ptr;
	t_philo	*tmp;

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

int
	main(int ac, char **av)
{
	struct timeval	c_time_start;
	t_philo			*philos;

	if (ac == 5 || ac == 6)
	{
		gen_philos(ac, av, &philos, &c_time_start);
		if (philos == NULL)
			return (free_philos(&philos));
		init_philos(&philos, &c_time_start, ft_atoi(av[2]));
		free_philos(&philos);
	}
	else
	{
		printf("Usage : ./philo_one nbr_of_philos time_to_die time_to_eat");
		printf(" time_to_sleep [minimum_eat_for_each_philos]\n");
	}
	return (0);
}
