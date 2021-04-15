/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:31:26 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/15 15:34:00 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	check_fork(t_philo *phi)
{
	sem_wait(phi->data->forks);
	phi->state = FORK;
	display_state(phi);
	display_state(phi);
	phi->state = EAT;
}
