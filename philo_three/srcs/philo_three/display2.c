/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:54:12 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/21 17:54:33 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int
	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static void
	ft_itobuff2(int iszero, unsigned int nu, int i, char *res)
{
	res[i] = '\0';
	while (nu > 0)
	{
		i--;
		res[i] = nu % 10 + '0';
		nu = nu / 10;
	}
	i--;
	if (iszero)
	{
		res[i] = nu + '0';
		i--;
	}
}

static int
	ft_itobuff(unsigned long int n, char *buffer)
{
	unsigned long int	nu;
	unsigned long int	i;
	int					iszero;

	i = 0;
	buffer[i] = '\0';
	if (n == 0)
	{
		i = 1;
		nu = 0;
	}
	else
		nu = n;
	iszero = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	if (nu == 0)
		iszero++;
	ft_itobuff2(iszero, nu, i, buffer);
	return (i);
}

static int
	str_cpy(char *str, char *buff)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		buff[i] = str[i];
		i++;
	}
	return (i);
}

void
	display_helper(unsigned long int time, int id, char *str)
{
	char	buff[34];
	int		i;

	i = ft_itobuff(time, buff);
	buff[i] = ' ';
	i = (i + 1 + ft_itobuff((unsigned long int)id, &buff[i + 1]));
	buff[i] = ' ';
	i = (i + 1 + str_cpy(str, &buff[i + 1]));
	buff[i] = '\n';
	buff[i + 1] = '\0';
	write(1, buff, ft_strlen(buff));
}
