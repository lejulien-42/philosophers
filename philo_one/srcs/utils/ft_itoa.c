/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 10:35:00 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/15 11:15:45 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_itoa2(int iszero, unsigned int nu, int i)
{
	char			*res;

	if (!(res = malloc((i + 1) * sizeof(char))))
		return (0);
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
	if (i == 0)
		res[i] = '-';
	return (res);
}

char		*ft_itoa(int n)
{
	unsigned int	nu;
	int				i;
	int				iszero;

	i = 0;
	if (n <= 0)
	{
		nu = -n;
		i++;
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
	return (ft_itoa2(iszero, nu, i));
}

static char	*ft_ulitoa2(int iszero, unsigned long int nu, int i)
{
	char			*res;

	if (!(res = malloc((i + 1) * sizeof(char))))
		return (0);
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
	if (i == 0)
		res[i] = '-';
	return (res);
}

char		*ft_ulitoa(unsigned long int n)
{
	unsigned long int	nu;
	int					i;
	int					iszero;

	i = 0;
	if (n <= 0)
	{
		nu = -n;
		i++;
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
	return (ft_itoa2(iszero, nu, i));
}
