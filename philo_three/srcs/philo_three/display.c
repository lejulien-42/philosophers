/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:13:20 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/19 17:32:25 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	display_state(t_philo *ptr)
{
	unsigned long int	time;
	int					i;

	if (ptr->data->is_dead)
		return ;
	sem_wait(ptr->data->write_access);
	time = ft_get_ct(&ptr->start);
	if (ptr->state == DIED)
	{
		ptr->data->is_dead = 1;
		printf("%ld %d has died\n", time, ptr->id + 1);
		i = -1;
		while (++i < ptr->data->nbr)
			sem_post(ptr->data->phi_filled);
		return ;
	}
	if (ptr->state == EAT)
		printf("%ld %d is eating\n", time, ptr->id + 1);
	if (ptr->state == SLEEP)
		printf("%ld %d is sleeping\n", time, ptr->id + 1);
	if (ptr->state == THINK)
		printf("%ld %d is thinking\n", time, ptr->id + 1);
	sem_post(ptr->data->write_access);
}
