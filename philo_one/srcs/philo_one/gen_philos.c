/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:14:26 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/14 15:14:57 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		phi->is_eating = 0;
		phi->nbr_of_lunch = 0;
		phi->data = data;
		phi->next = NULL;
		if (phi->id == 0)
			phi->fork_l = &data->forks[data->nbr - 1];
		else
			phi->fork_l = &data->forks[phi->id - 1];
		phi->fork_r = &data->forks[phi->id];
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

