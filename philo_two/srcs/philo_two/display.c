/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:13:20 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/17 17:02:13 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	display_state(t_philo *ptr)
{
	unsigned long int	time;

	if (ptr->data->is_dead)
		return ;
	time = ft_get_ct(&ptr->start);
	if (ptr->state == DIED)
	{
		ptr->data->is_dead = 1;
		printf("%ld %d has died | %ld\n", time, ptr->id + 1, ptr->last_eat);
	}
	if (ptr->state == EAT)
		printf("%ld %d is eating\n", time, ptr->id + 1);
	if (ptr->state == SLEEP)
		printf("%ld %d is sleeping\n", time, ptr->id + 1);
	if (ptr->state == THINK)
		printf("%ld %d is thinking\n", time, ptr->id + 1);
}
