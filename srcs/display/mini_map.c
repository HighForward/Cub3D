/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 23:23:18 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/22 01:28:12 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_map(t_data *data)
{
	int i;

	i = 0;
	while (data->map[i])
	{
		ft_putpixel(data->map[i], i, data);
		i++;
	}
}

void	ft_putpixel(char *line, int i, t_data *data)
{
	int x;
	int y;
	int index;
	int color;

	index = 0;
	x = 0;
	y = (i * ((data->info->width + data->info->height) / 250));
	while (line[index])
	{
		if (line[index] == '1')
			color = convertrgb(0, 0, 0);
		else if (line[index] == 'D')
			color = convertrgb(170, 170, 170);
		else if (line[index] == 'H')
			color = convertrgb(153, 0, 110);
		else if (line[index] == '2')
			color = convertrgb(255, 255, 255);
		else
			color = convertrgb(255, 0, 0);
		display_rekt(x, y, color, data);
		x += ((data->info->width + data->info->height) / 250);
		index++;
	}
}

void	display_rekt(int x, int y, int color, t_data *data)
{
	t_index t;
	int		count;
	t_color	w;
	t_color	z;
	t_color	final;

	count = 1;
	t.i = x;
	t.j = y;
	while (x < t.i + ((data->info->width + data->info->height) / 250))
	{
		y = t.j;
		while (y < t.j + ((data->info->width + data->info->height) / 250))
		{
			w = c(color);
			z = c(data->image->img_data[y * data->info->width + x]);
			final.rgba.r = get_transparency(data, w.rgba.r, z.rgba.r);
			final.rgba.g = get_transparency(data, w.rgba.g, z.rgba.g);
			final.rgba.b = get_transparency(data, w.rgba.b, z.rgba.b);
			data->image->img_data[y * data->info->width + x] = color;
			y++;
		}
		x++;
	}
}

void	display_dir_map(t_data *data)
{
	int			i;
	t_vector	step;
	t_ray		ray;
	float		camera;

	step.x = data->player->d.x;
	step.y = data->player->d.y;
	ray.i = 0;
	while (ray.i++ < data->info->width)
	{
		camera = 2.0f * ray.i / data->info->width - 1.0f;
		ray.x = data->player->d.x + data->player->p.x * camera;
		ray.y = data->player->d.y + data->player->p.y * camera;
		i = 0;
		while (i < ((data->info->width + data->info->height) / 250))
		{
			data->image->img_data[(int)((data->player->y * ((data->info->width +
			data->info->height) / 250)) + (i * ray.y)) * data->info->width +
			(int)((data->player->x * ((data->info->width + data->info->height)
			/ 250)) + (i * ray.x))] = convertrgb(0, 255, 255);
			i++;
		}
	}
	secure_vector(step, data, i);
}

void	secure_vector(t_vector step, t_data *data, int i)
{
	while (i < (2 * ((data->info->width + data->info->height) / 250)))
	{
		if ((((int)((data->player->y * ((data->info->width + data->info->height)
			/ 250)) + (i * step.y))) > 0) && ((int)((data->player->x *
			((data->info->width + data->info->height) / 250)) + (i * step.x)) <
			(ft_strlen(data->map[0]) * ((data->info->width + data->info->height)
			/ 250))) && ((int)((data->player->y * ((data->info->width +
			data->info->height) / 250)) + (i * step.y)) < (size_map(data->map) *
			((data->info->width + data->info->height) / 250))) &&
			((int)((data->player->x * ((data->info->width + data->info->height)
			/ 250)) + (i * step.x)) > 0))
			data->image->img_data[(int)((data->player->y * ((data->info->width +
			data->info->height) / 250)) + (i * step.y)) * data->info->width +
			(int)((data->player->x * ((data->info->width + data->info->height)
			/ 250)) + (i * step.x))] = convertrgb(0, 0, 0);
		i++;
	}
}
