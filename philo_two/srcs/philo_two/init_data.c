/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:07:28 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/21 17:32:23 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int
	check_int(char **av, int index)
{
	int		test_i;
	char	*test;

	test_i = ft_atoi(av[index]);
	if (test_i > 100000)
		return (1);
	test = ft_itoa(test_i);
	if (ft_strcmp(av[index], test))
	{
		free(test);
		return (1);
	}
	free(test);
	return (0);
}

static int
	check_uli(char **av, int index)
{
	int		test_i;
	char	*test;

	if (av[index][0] == '-')
		return (1);
	test_i = ft_atouli(av[index]);
	test = ft_ulitoa(test_i);
	if (ft_strcmp(av[index], test))
	{
		free(test);
		return (1);
	}
	free(test);
	return (0);
}

static int
	check_data(int ac, char **av)
{
	if (check_int(av, 1))
		return (1);
	if (ft_atoi(av[1]) < 1)
		return (1);
	if (check_uli(av, 2))
		return (1);
	if (check_uli(av, 3))
		return (1);
	if (check_uli(av, 4))
		return (1);
	if (ac == 6)
	{
		if (check_int(av, 5))
			return (1);
		if (ft_atoi(av[5]) < 1)
			return (1);
	}
	return (0);
}

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
	if (ac == 6)
		data->max_launch = ft_atoi(av[5]);
	else
		data->max_launch = -1;
}

t_data
	*init_data(int ac, char **av)
{
	t_data	*data;
	int		i;

	if (check_data(ac, av) || !(data = malloc(sizeof(t_data))))
		return (NULL);
	data->is_dead = 0;
	i = 0;
	init_data_helper(data, ac, av);
	sem_unlink("forks");
	sem_unlink("write_access");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->nbr / 2);
	data->write_access = sem_open("write_access", O_CREAT | O_EXCL, 0644, 1);
	return (data);
}
