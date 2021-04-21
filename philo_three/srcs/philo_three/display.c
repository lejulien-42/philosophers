/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:13:20 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/21 17:54:31 by lejulien         ###   ########.fr       */
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
		display_helper(time, ptr->id + 1, "died");
		i = -1;
		while (++i < ptr->data->nbr)
			sem_post(ptr->data->phi_filled);
		return ;
	}
	if (ptr->state == EAT)
		display_helper(time, ptr->id + 1, "is eating");
	if (ptr->state == SLEEP)
		display_helper(time, ptr->id + 1, "is sleeping");
	if (ptr->state == THINK)
		display_helper(time, ptr->id + 1, "is thinking");
	sem_post(ptr->data->write_access);
}
