/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:42:30 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/08 17:23:14 by lejulien         ###   ########.fr       */
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
	gen_philos(int ac, char **av, t_philo **philos, t_data *data)
{
	int				i;
	t_philo			*phi;
	t_philo			*ptr;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		ptr = *philos;
		if (!(phi = malloc(sizeof(t_philo))))
			return ;
		phi->id = i;
		phi->state = SLEEP;
		phi->last_eat = 0;
		phi->nbr_of_lunch = 0;
		phi->data = data;
		phi->next = NULL;
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

static t_data
	*init_data(int ac, char **av, struct timeval *c_time_start, pthread_mutex_t *write_access)
{
	t_data	*data;
	int		i;

	i = 0;
	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
	if (!(data->forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t))))    // free this later
		return (NULL);
	if (!(data->forks_status = malloc(ft_atoi(av[1]) * sizeof(int))))    // free this
		return (NULL);
	if (!(data->is_a_dead_guy = malloc(sizeof(int))))    // free this
		return (NULL);
	data->is_a_dead_guy[0] = 0;
	while (i < ft_atoi(av[1]))
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (NULL);
		data->forks_status[i] = 1;
		i++;
	}
	data->nbr = ft_atoi(av[1]);
	data->time_to_die = ft_atouli(av[2]);
	data->time_to_eat = ft_atouli(av[3]);
	data->time_to_sleep = ft_atouli(av[4]);
	data->nbr = ft_atoi(av[1]);
	if (ac == 6)
		data->max_launch = ft_atoi(av[5]);
	else
		data->max_launch = -1;
	if (!(data->write_access_i = malloc(sizeof(int))))    // free this
		return (NULL);
	data->write_access_i[0] = 1;
	data->write_access_m = write_access;
	data->c_time_start = c_time_start;
	return (data);
}

int
	main(int ac, char **av)
{
	t_philo			*philos;
	t_data			*data;
	struct timeval	c_time_start;
	pthread_mutex_t	write_access;


	philos = NULL;
	if (ac == 5 || ac == 6)
	{
		if (pthread_mutex_init(&write_access, NULL) != 0)
			return (1);
		if (!(data = init_data(ac, av, &c_time_start, &write_access)))
			return (1);
		gen_philos(ac, av, &philos, data);
		if (philos == NULL)
			return (free_philos(&philos));
		init_philos(&philos, &c_time_start, ft_atoi(av[2]));
		free(data->forks);
		free(data->forks_status);
		free(data);
		free_philos(&philos);
	}
	else
	{
		printf("Usage : ./philo_one nbr_of_philos time_to_die time_to_eat");
		printf(" time_to_sleep [minimum_eat_for_each_philos]\n");
	}
	return (0);
}
