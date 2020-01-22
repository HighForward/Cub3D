/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 00:29:25 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/22 00:29:25 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		get_value_window(char *s, int *i)
{
	int nb;
	int x;

	x = 0;
	nb = 0;
	if ((s[x] >= '0' && s[x] <= '9'))
	{
		while ((s[x] && (s[x] >= '0' && s[x] <= '9')))
		{
			nb = nb * 10 + (s[x] - 48);
			(x)++;
		}
		(*i) += x;
		return (nb);
	}
	return (0);
}

int		skip_space(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int		skip_space_virgule(char *str, int *i)
{
	int x;
	int virgule;

	x = 0;
	virgule = 0;
	while (str[x] && (str[x] == ' ' || str[x] == ','))
	{
		if (str[x] == ',')
			virgule++;
		x++;
	}
	if (virgule != 1 || x < 1)
		return (0);
	(*i) += x;
	return (1);
}
