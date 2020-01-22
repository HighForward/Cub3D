/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:33:27 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/21 21:35:39 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		map_is_not_close(t_data *data)
{
	t_index x;
	t_index y;

	x = vec_i(0, 0);
	y = vec_i(0, 0);
	while (data->map[y.i])
		y.i++;
	while (data->map[x.j])
	{
		if (y.j != 0 && y.j != ft_strlen(data->map[x.j]))
			return (return_string(0, "Error\nWrong length\n"));
		x.i = 0;
		while (data->map[x.j][x.i])
		{
			if ((x.j == 0 || x.j == y.i - 1) && data->map[x.j][x.i] != '1')
				return (return_string(0, "Error\nMap isn't close\n"));
			if ((x.i == 0 || x.i == ft_strlen(data->map[x.j]) - 1) &&
				data->map[x.j][x.i] != '1')
				return (return_string(0, "Error\nMap isn't close\n"));
			x.i++;
		}
		y.j = ft_strlen(data->map[x.j]);
		x.j++;
	}
	return (1);
}

int		map_too_big(t_data *data)
{
	if ((size_map(data->map) * ((data->info->width +
		data->info->height) / 250)) > data->info->height)
		return (return_string(0, "Error\nMap Height too big\n"));
	if ((ft_strlen(data->map[0]) * ((data->info->width +
		data->info->height) / 250)) > data->info->width)
		return (return_string(0, "Error\nMap Width too big\n"));
	return (1);
}

int		check_map_parsing(t_data *data)
{
	if (data->map == NULL)
		return (0);
	if (fill_full_map(data) == 0)
		return (0);
	if ((get_position(data)) == 0)
		return (0);
	if ((map_is_not_close(data)) == 0)
		return (0);
	if ((map_too_big(data)) == 0)
		return (0);
	return (1);
}
