/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:30:56 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/21 21:33:25 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		is_valid_line(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '1' && s[i] != '0' && s[i] != 'D'
			&& s[i] != 'N' && s[i] != 'S' && s[i] != 'E'
			&& s[i] != 'W' && s[i] != 'H' && s[i] != '2')
		{
			free(s);
			return (0);
		}
		i++;
	}
	return (1);
}

void	cut_space(char **line)
{
	int		i;
	int		space;
	char	*dup;

	space = 0;
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i++] != ' ')
			space++;
	}
	dup = ft_strnew(space);
	space = 0;
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i++] != ' ')
		{
			dup[space] = (*line)[i - 1];
			space++;
		}
	}
	dup[space] = '\0';
	free((*line));
	(*line) = dup;
}

int		free_entire_map(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_bzero(str[i], ft_strlen(str[i]));
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
	return (1);
}
