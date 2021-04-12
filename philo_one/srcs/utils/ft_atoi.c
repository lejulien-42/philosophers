/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:06:04 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/04 16:10:27 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int
	ft_isspace(char c)
{
	if ((c == '\f') || (c == '\t') || (c == '\n') || (c == '\r')
		|| (c == '\v') || (c == ' '))
	{
		return (1);
	}
	return (0);
}

int
	ft_atoi(const char *str)
{
	int nbr;
	int sign;
	int index;

	nbr = 0;
	sign = 1;
	index = 0;
	while ((ft_isspace(str[index]) == 1) && str[index] != '\0')
		index++;
	if ((str[index] == '+') || (str[index] == '-'))
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while ((str[index] >= '0') && (str[index] <= '9'))
	{
		nbr = (nbr * 10) + (str[index] - '0');
		index++;
	}
	return (sign * nbr);
}

unsigned long int
	ft_atouli(const char *str)
{
	unsigned long int	nbr;
	int					sign;
	unsigned long int	index;

	nbr = 0;
	sign = 1;
	index = 0;
	while ((ft_isspace(str[index]) == 1) && str[index] != '\0')
		index++;
	if ((str[index] == '+') || (str[index] == '-'))
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while ((str[index] >= '0') && (str[index] <= '9'))
	{
		nbr = (nbr * 10) + (str[index] - '0');
		index++;
	}
	return (sign * nbr);
}
