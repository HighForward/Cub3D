/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:04:46 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/09 09:08:31 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    take_damage(t_data *data, int value)
{
	int j;
	int i;

	j = 0;
	data->player->life -= value;
	if (data->player->life == 0)
	{
		data->player->life = 100;
		data->player->x = data->player->spawn.spawn_x + 0.20f;
		data->player->y = data->player->spawn.spawn_y + 0.20f;
	}
}

void    handle_secret_door(t_data *data, t_render *render, t_ray ray)
{
	if (data->map[render->map_y][render->map_x] == 'D')
		render->secret_door = 1;
	else if (data->map[render->map_y][render->map_x] == 'H')
		render->secret_door = 2;
	if (data->secret_key == 1 && (data->map[render->map_y][render->map_x] == 'D' || data->map[render->map_y][render->map_x] == 'H') && ray.i == data->info->width / 2 && render->blockdist < 3)
	{
		if (data->map[render->map_y][render->map_x] == 'D')
			data->map[render->map_y][render->map_x] = 'X';
		else if (data->map[render->map_y][render->map_x] == 'H')
			data->map[render->map_y][render->map_x] = 'B';
		render->secret_door = 0;
		display_view(data->player, data);
	}
	else
		render->hit = 1;
}

void    leave_secret_door(t_data *data)
{
	static char last_pos;
	static int last_pos_x;
	static int last_pos_y;

	if (last_pos == 'X' && data->map[(int)data->player->y][(int)data->player->x] == '0')
		data->map[last_pos_x][last_pos_y] = 'D';
	if (last_pos == 'B' && data->map[(int)data->player->y][(int)data->player->x] == '0')
		data->map[last_pos_x][last_pos_y] = 'H';

	last_pos = data->map[(int)data->player->y][(int)data->player->x];
	last_pos_x = (int)data->player->y;
	last_pos_y = (int)data->player->x;
}