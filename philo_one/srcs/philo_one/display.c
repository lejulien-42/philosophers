/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:02:58 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/08 17:26:01 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	display_state(t_philo *ptr)
{
	if (!ptr->data->write_access_i[0])
		return ;
	pthread_mutex_lock(ptr->data->write_access_m);
	if (ptr->state == 0)
		printf("\033[0;31m[%ld] %d has died\n\033[0;37m", ft_get_ct(ptr->data->c_time_start), ptr->id + 1);
	else if (ptr->state == 1)
		printf("\033[0;32m[%ld] %d is eating\n\033[0;37m", ft_get_ct(ptr->data->c_time_start), ptr->id + 1);
	else if (ptr->state == 2)
		printf("\033[0;34m[%ld] %d is sleeping\n\033[0;37m", ft_get_ct(ptr->data->c_time_start), ptr->id + 1);
	else if (ptr->state == 3)
		printf("\033[0;33m[%ld] %d is thinking\n\033[0;37m", ft_get_ct(ptr->data->c_time_start), ptr->id + 1);
	else if (ptr->state == 4)
		printf("\033[0;37m[%ld] %d has taken a fork\n\033[0;37m", ft_get_ct(ptr->data->c_time_start), ptr->id + 1);
	pthread_mutex_unlock(ptr->data->write_access_m);
}
