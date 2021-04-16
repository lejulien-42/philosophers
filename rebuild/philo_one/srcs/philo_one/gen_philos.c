/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:59:19 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/16 15:17:35 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo
	*gen_philos(int ac, char **av, t_data *data)
{
	int	i;
	t_philo	*philos;

	if (!(philos = malloc(ft_atoi(av[1]) * sizeof(t_philo))))
		return (NULL);
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		philos[i].id = i;
		philos[i].state = SLEEP;
		philos[i].last_eat = SLEEP;
		philos[i].nbr_of_eats = 0;
		philos[i].data = data;
		if (i == 0)
			philos[i].fork_l = &data->forks[data->nbr - 1];
		else
			philos[i].fork_l = &data->forks[i - 1];
		philos[i].fork_r = &data->forks[i];
	}
	return (philos);
}
