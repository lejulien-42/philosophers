/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:02:58 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/13 14:40:07 by lejulien         ###   ########.fr       */
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
		printf("\033[0;31m[%ld] %d has died\n\033[0;37m", time, ptr->id + 1);
	}
	if (!ptr->data->is_a_dead_guy && ptr->state == EAT)
		printf("\033[0;32m[%ld] %d is eating\n\033[0;37m", time, ptr->id + 1);
	if (!ptr->data->is_a_dead_guy && ptr->state == SLEEP)
		printf("\033[0;34m[%ld] %d is sleeping\n\033[0;37m", time, ptr->id + 1);
	if (!ptr->data->is_a_dead_guy && ptr->state == THINK)
		printf("\033[0;33m[%ld] %d is thinking\n\033[0;37m", time, ptr->id + 1);
	if (!ptr->data->is_a_dead_guy && ptr->state == FORK)
		printf("\033[0;37m[%ld] %d has taken a fork\n\033[0;37m", time, ptr->id + 1);
}
