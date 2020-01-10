/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 08:35:45 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/10 10:52:52 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void     get_orientation(t_data *data, float x, float y, float cam_x, float cam_y)
{
	data->player->d.x = x;
	data->player->d.y = y;
	data->player->p.x = cam_x;
	data->player->p.y = cam_y;
}

int     get_position(t_data *data)
{
	int j;
	int i;
	float step_player;
	int player_there;

	player_there = 0;
	step_player = STEP > 1.0f ? 1.0f : STEP;
	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == 'W' || data->map[j][i] == 'E' || data->map[j][i] == 'N' || data->map[j][i] == 'S')
			{
				if (data->map[j][i] == 'W')
					get_orientation(data, -1.0f, 0.0f, 0.0f, -0.6f);
				if (data->map[j][i] == 'N')
					get_orientation(data, 0.0f, -1.0f, 0.6f, 0.0f);
				if (data->map[j][i] == 'S')
					get_orientation(data, 0.0f, 1.0f, -0.6f, 0.0f);
				if (data->map[j][i] == 'E')
					get_orientation(data, 1.0f, 0.0f, 0.0f, 0.6f);
				data->player->view = VIEW;
				data->player->move = step_player;
				data->player->x = i + 0.49;
				data->player->y = j + 0.49;
				data->player->spawn.spawn_x = i;
				data->player->spawn.spawn_y = j;
				data->player->life = 100;
				player_there++;
			}
			i++;
		}
		j++;
	}
	if (player_there != 1)
		return (return_string(0, "Error\nWrong Player location\n"));
	return (1);
}

int     map_is_not_close(t_data *data)
{
	int i;
	int j;
	int len;
	int size;

	size = 0;
	j = 0;
	len = 0;
	while (data->map[size])
		size++;
	while (data->map[j])
	{
		if (len != 0 && len != ft_strlen(data->map[j]))
			return (return_string(0, "Error\nWrong length\n"));
		i = 0;
		while (data->map[j][i])
		{
			if ((j == 0 || j == size - 1) && data->map[j][i] != '1')
				return (return_string(0, "Error\nMap isn't close\n"));
			if ((i == 0 || i == ft_strlen(data->map[j]) - 1) && data->map[j][i] != '1')
				return (return_string(0, "Error\nMap isn't close\n"));
			i++;
		}
		len = ft_strlen(data->map[j]);
		j++;
	}
	return (1);
}

int     is_valid_line(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '1' && s[i] != '0' && s[i] != 'D' && s[i] != 'N' && s[i] != 'S' && s[i] != 'E' && s[i] != 'W'  && s[i] != 'H' && s[i] != '2')
			return (0);
		i++;
	}
	return (1);
}