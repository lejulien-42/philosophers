/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:46:04 by lejulien          #+#    #+#             */
/*   Updated: 2021/04/15 10:58:32 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(char *s1, char *s2)
{
	int index;

	index = 0;
	while (s2[index] && s1[index])
	{
		if (s1[index] == s2[index])
			index++;
		else
			return (1);
	}
	if (s1[index] == '\0' && s2[index] == '\0')
		return (0);
	return (1);
}
