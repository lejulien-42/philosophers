/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:02:58 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/15 13:32:51 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	display_state(t_philo *ptr)
{
	unsigned long int	time;

	if (ptr->data->is_a_dead_guy && !ptr->data->started)
		return ;
	time = ft_get_ct(ptr->data->c_time_start);
	if (!ptr->data->is_a_dead_guy && ptr->state == DIED)
	{
		ptr->data->is_a_dead_guy = 1;
		printf("%ld %d has died\n", time, ptr->id + 1);
	}
	if (!ptr->data->is_a_dead_guy && ptr->state == EAT)
		printf("%ld %d is eating\n", time, ptr->id + 1);
	if (!ptr->data->is_a_dead_guy && ptr->state == SLEEP)
		printf("%ld %d is sleeping\n", time, ptr->id + 1);
	if (!ptr->data->is_a_dead_guy && ptr->state == THINK)
		printf("%ld %d is thinking\n", time, ptr->id + 1);
	if (!ptr->data->is_a_dead_guy && ptr->state == FORK)
		printf("%ld %d has taken a fork\n",
				time, ptr->id + 1);
}
