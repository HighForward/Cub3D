/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:04:46 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/18 11:58:09 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void display_hud(t_data *data)
{
	float echX;
	float echY;
	float step_x;
	float step_y;
	int i;
	int j;

	echX = (float) data->tex->hud.img_width / (float) data->info->width;
	echY = (float) data->tex->hud.img_height / (float) data->info->height;
	step_x = 0;
	step_y = 0;
	i = 0;
	while (i < data->info->height)
	{
		j = 0;
		step_x = 0;
		while (j < data->info->width)
		{
			if (data->tex->hud.add_tex[((int) step_y) * data->tex->hud.img_width + ((int) step_x)] !=
				convertRGB(255, 0, 0))
				data->image->img_data[i * data->info->width + j] = data->tex->hud.add_tex[
						((int) step_y) * data->tex->hud.img_width + ((int) step_x)];
			step_x += echX;
			j++;
		}
		step_y += echY;
		i++;
	}
}

void display_dead_screen(t_data *data, int key)
{
	float echX;
	float echY;
	float step_x;
	float step_y;
	int i;
	int j;

	echX = (float) data->tex->dead.img_width / (float) data->info->width;
	echY = (float) data->tex->dead.img_height / (float) data->info->height;
	step_x = 0;
	step_y = 0;
	i = 0;
	while (i < data->info->height)
	{
		j = 0;
		step_x = 0;
		while (j < data->info->width)
		{
			data->image->img_data[i * data->info->width + j] = data->tex->dead.add_tex[
					((int) step_y) * data->tex->dead.img_width + ((int) step_x)];
			step_x += echX;
			j++;
		}
		step_y += echY;
		i++;
	}
	if (key == 49)
	{
		data->player->dead = 0;
		display(data, 0);
	}
}

void take_damage(t_data *data, int value)
{
	int j;
	int i;

	j = 0;
	data->player->life -= value;
	if (data->player->life <= 0)
	{
		data->player->life = 100;
		data->player->x = data->player->spawn.spawn_x + 0.20f;
		data->player->y = data->player->spawn.spawn_y + 0.20f;
		data->player->dead = 1;
	}
}

void handle_secret_door(t_data *data, t_render *render, t_ray ray)
{
	if (data->map[render->map_y][render->map_x] == 'D')
		render->secret_door = 1;
	else if (data->map[render->map_y][render->map_x] == 'H')
		render->secret_door = 2;
	if (data->secret_key == 1 &&
		(data->map[render->map_y][render->map_x] == 'D' || data->map[render->map_y][render->map_x] == 'H') &&
		ray.i == data->info->width / 2 && render->blockdist < 3)
	{
		if (data->map[render->map_y][render->map_x] == 'D')
			data->map[render->map_y][render->map_x] = 'X';
		else if (data->map[render->map_y][render->map_x] == 'H')
			data->map[render->map_y][render->map_x] = 'B';
		render->secret_door = 0;
		display_view(data->player, data);
	} else
		render->hit = 1;
}

void leave_secret_door(t_data *data)
{
	static char last_pos;
	static int last_pos_x;
	static int last_pos_y;

	if (last_pos == 'X' && data->map[(int) data->player->y][(int) data->player->x] == '0')
		data->map[last_pos_x][last_pos_y] = 'D';
	if (last_pos == 'B' && data->map[(int) data->player->y][(int) data->player->x] == '0')
		data->map[last_pos_x][last_pos_y] = 'H';

	last_pos = data->map[(int) data->player->y][(int) data->player->x];
	last_pos_x = (int) data->player->y;
	last_pos_y = (int) data->player->x;
}

int get_darkness(int color, int percent)
{

	t_color current;
	t_color darkness;
	int coeff;

	percent += 15;
	coeff = percent > 100 ? 100 : percent;
	current.value = color;
	darkness.rgba.r = (current.rgba.r * coeff / 100);
	darkness.rgba.g = (current.rgba.g * coeff / 100);
	darkness.rgba.b = (current.rgba.b * coeff / 100);
	return (darkness.value);
}