/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:02:58 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/10 17:51:42 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	display_state(t_philo *ptr)
{
	unsigned long int	time;
	if (ptr->data->is_a_dead_guy)
		return ;

	if (ptr->data->started)
		time = ft_get_ct(ptr->data->c_time_start);
	else
		return ;
	if (ptr->state == 0)
		printf("\033[0;31m[%ld] %d has died\n\033[0;37m", time, ptr->id + 1);
	if (ptr->state == 1)
		printf("\033[0;32m[%ld] %d is eating\n\033[0;37m", time, ptr->id + 1);
	if (ptr->state == 2)
		printf("\033[0;34m[%ld] %d is sleeping\n\033[0;37m", time, ptr->id + 1);
	if (ptr->state == 3)
		printf("\033[0;33m[%ld] %d is thinking\n\033[0;37m", time, ptr->id + 1);
	if (ptr->state == 4)
		printf("\033[0;37m[%ld] %d has taken a fork\n\033[0;37m", time, ptr->id + 1);
}
