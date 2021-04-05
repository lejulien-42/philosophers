/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:02:58 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/05 15:20:05 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	display_state(t_philo **phi)
{
	t_philo	*ptr;

	ptr = *phi;
	if (ptr->state == 0)
		printf("[%ld] %d has died\n", ft_get_ct(ptr->c_time_start), ptr->id);
	else if (ptr->state == 1)
		printf("[%ld] %d is eating\n", ft_get_ct(ptr->c_time_start), ptr->id);
	else if (ptr->state == 2)
		printf("[%ld] %d is sleeping\n", ft_get_ct(ptr->c_time_start), ptr->id);
	else if (ptr->state == 3)
		printf("[%ld] %d is thinking\n", ft_get_ct(ptr->c_time_start), ptr->id);
	else if (ptr->state == 4)
		printf("[%ld] %d has taken a fork\n", ft_get_ct(ptr->c_time_start), ptr->id);
}
