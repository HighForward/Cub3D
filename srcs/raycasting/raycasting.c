/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:07:31 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/22 05:27:13 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			display_view(t_player *p, t_data *data)
{
	float	camera;
	t_ray	ray;

	ray.i = 0;
	data->sprite.last = 0;
	while (ray.i < data->info->width)
	{
		camera = 2.0f * ray.i / data->info->width - 1.0f;
		ray.x = data->player->d.x + data->player->p.x * camera;
		ray.y = data->player->d.y + data->player->p.y * camera;
		if (get_wall(data, ray) == 0)
			return (0);
		ray.i++;
	}
	return (1);
}

t_tex_info	current_texture(t_data *data, t_render render)
{
	if (render.side == 1 && render.step_y == 1 && render.secret_door != 1)
		return (data->tex->north);
	else if (render.side == 1 && render.step_y == -1 && render.secret_door != 1)
		return (data->tex->south);
	else if (render.side == 0 && render.step_x == -1 && render.secret_door != 1)
		return (data->tex->east);
	else if (render.side == 0 && render.step_x == 1 && render.secret_door != 1)
		return (data->tex->west);
	else
		return (data->tex->door);
}

void		print_lines(t_data *data, t_ray ray, t_render render, int *buffer)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (x < data->info->height)
	{
		if (x > render.drawstart && x < render.drawend)
		{
			data->image->img_data[(x) * data->info->width + ray.i] = buffer[i];
			i++;
		}
		else if (x <= render.drawstart)
			data->image->img_data[(x) * data->info->width + ray.i] =
					data->info->color_cellar;
		else if (x >= render.drawend && x < data->info->height)
			data->image->img_data[(x) * data->info->width + ray.i] =
					data->info->color_floor;
		x++;
	}
}

int			get_line(t_data *data, t_ray ray, t_render render)
{
	int		*buffer;
	int		i;
	int		x;

	i = 0;
	x = 0;
	render.drawstart = 0;
	render.drawend = 0;
	render.lineheight = (int)(data->info->height / render.dist_wall);
	render.drawstart = (-render.lineheight / 2 + (data->info->height / 2));
	render.drawend = (render.lineheight / 2 + data->info->height / 2);
	if (render.drawstart < 0)
		render.drawstart = 0;
	if (render.drawend >= data->info->height)
		render.drawend = data->info->height - 1;
	if (!(buffer = malloc(sizeof(int) * (render.lineheight + 1))))
		return (0);
	load_line_buffer(data, render, ray, &buffer);
	print_lines(data, ray, render, buffer);
	free(buffer);
	buffer = NULL;
	return (1);
}

int			get_wall(t_data *data, t_ray ray)
{
	t_render render;

	render.secret_door = 0;
	render.dist_wall = 0.0f;
	render.blockdist = 0;
	render.hit = 0;
	render.map_x = (int)data->player->x;
	render.map_y = (int)data->player->y;
	render.dist_x = sqrt(1 + (ray.y * ray.y) / (ray.x * ray.x));
	render.dist_y = sqrt(1 + (ray.x * ray.x) / (ray.y * ray.y));
	render.step_x = ray.x < 0 ? -1 : 1;
	render.step_y = ray.y < 0 ? -1 : 1;
	render.sidedist_x =
			(ray.x < 0 ? data->player->x - render.map_x : render.map_x +
			1.0f - data->player->x) * render.dist_x;
	render.sidedist_y =
			(ray.y < 0 ? data->player->y - render.map_y : render.map_y +
			1.0f - data->player->y) * render.dist_y;
	get_wall_dda(data, &render, ray);
	render.current = current_texture(data, render);
	if (!(get_line(data, ray, render)))
		return (0);
	display_sprite(data, ray);
	return (1);
}
