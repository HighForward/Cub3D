/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:07:22 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/16 16:35:54 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int display_view(t_player *p, t_data *data)
{
	float camera;
	t_ray ray;

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

t_tex_info current_texture(t_data *data, t_render render)
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

void load_line_buffer(t_data *data, t_render render, t_ray ray, int **buffer)
{
	int y;
	int i;
	t_graphic tex;

	i = 0;
	if (render.side == 0)
		tex.wallX = data->player->y + render.perpWallDist * ray.y;
	else
		tex.wallX = data->player->x + render.perpWallDist * ray.x;
	tex.wallX = tex.wallX - floor((tex.wallX));
	tex.texX = (int) (tex.wallX * render.current.img_width);
	if (render.side == 0 && ray.x > 0)
		tex.texX = render.current.img_width - tex.texX - 1;
	if (render.side == 1 && ray.y < 0)
		tex.texX = render.current.img_width - tex.texX - 1;
	tex.step = 1.0f * render.current.img_height / render.lineHeight;
	tex.texPos = (render.drawstart - ((data->info->height / 2)) + (render.lineHeight / 2)) * tex.step;
	y = render.drawstart;
	while (y < render.drawend)
	{
		tex.texY = (int) tex.texPos & (render.current.img_height) - 1;
		tex.texPos += tex.step;
		(*buffer)[i] = get_darkness(render.current.add_tex[render.current.img_height * tex.texY + tex.texX],
									render.lineHeight);
		i++;
		y++;
	}
}

void print_lines(t_data *data, t_ray ray, t_render render, int *buffer)
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
		} else if (x <= render.drawstart)
			data->image->img_data[(x) * data->info->width + ray.i] = data->info->color_cellar;
		else if (x >= render.drawend && x < data->info->height)
			data->image->img_data[(x) * data->info->width + ray.i] = data->info->color_floor;
		x++;
	}
}

int get_line(t_data *data, t_ray ray, t_render render)
{
	int *buffer;
	int i;
	int x;

	i = 0;
	x = 0;
	render.drawstart = 0;
	render.drawend = 0;
	render.lineHeight = (int) (data->info->height / render.perpWallDist);
	render.drawstart = (-render.lineHeight / 2 + (data->info->height / 2));
	render.drawend = (render.lineHeight / 2 + data->info->height / 2);
	if (render.drawstart < 0)
		render.drawstart = 0;
	if (render.drawend >= data->info->height)
		render.drawend = data->info->height - 1;
	if (!(buffer = malloc(sizeof(int) * (render.lineHeight + 1))))
		return (0);
	load_line_buffer(data, render, ray, &buffer);
	print_lines(data, ray, render, buffer);
	free(buffer);
	buffer = NULL;
	return (1);
}

void get_wall_dda(t_data *data, t_render *render, t_ray ray)
{
	data->sprite.is = 0;

	while (render->hit == 0)
	{
		if (render->sideDistX < render->sideDistY)
		{
			render->sideDistX = render->sideDistX + render->deltaDistX;
			render->map_x = render->map_x + render->step_x;
			render->side = 0;
		} else
		{
			render->sideDistY = render->sideDistY + render->deltaDistY;
			render->map_y = render->map_y + render->step_y;
			render->side = 1;
		}
		if (data->map[render->map_y][render->map_x] == '1')
			render->hit = 1;
		else if (data->map[render->map_y][render->map_x] == '2')
		{
			data->sprite.x = render->map_x;
			data->sprite.y = render->map_y;
			//data->sprite.Perp = render->perpWallDist;
		} else if (data->map[render->map_y][render->map_x] == 'D' || data->map[render->map_y][render->map_x] == 'H')
			handle_secret_door(data, render, ray);
		render->blockdist++;
	}
	if (render->side == 0)
		render->perpWallDist = (render->map_x - data->player->x + (1 - render->step_x) / 2) / ray.x;
	else
		render->perpWallDist = (render->map_y - data->player->y + (1 - render->step_y) / 2) / ray.y;
	data->sprite.Perp = render->perpWallDist;
}

int get_wall(t_data *data, t_ray ray)
{
	t_render render;
	render.secret_door = 0;
	render.perpWallDist = 0.0f;
	render.blockdist = 0;
	render.hit = 0;
	render.map_x = (int) data->player->x;
	render.map_y = (int) data->player->y;
	render.deltaDistX = sqrt(1 + (ray.y * ray.y) / (ray.x * ray.x));
	render.deltaDistY = sqrt(1 + (ray.x * ray.x) / (ray.y * ray.y));
	render.step_x = ray.x < 0 ? -1 : 1;
	render.step_y = ray.y < 0 ? -1 : 1;
	render.sideDistX =
			(ray.x < 0 ? data->player->x - render.map_x : render.map_x + 1.0f - data->player->x) * render.deltaDistX;
	render.sideDistY =
			(ray.y < 0 ? data->player->y - render.map_y : render.map_y + 1.0f - data->player->y) * render.deltaDistY;
	get_wall_dda(data, &render, ray);
	render.current = current_texture(data, render);
	if (!(get_line(data, ray, render)))
		return (0);
	display_sprite(data, ray);
	return (1);
}
