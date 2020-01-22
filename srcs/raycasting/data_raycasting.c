/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:37:35 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/22 05:27:13 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		get_wall_dda(t_data *data, t_render *render, t_ray ray)
{
	while (render->hit == 0)
	{
		if (render->sidedist_x < render->sidedist_y)
			side_x(render);
		else
			side_y(render);
		if (data->map[render->map_y][render->map_x] == '1')
			render->hit = 1;
		else if (data->map[render->map_y][render->map_x] == '2')
			hit_sprite(data, render);
		else if (data->map[render->map_y][render->map_x] == 'D'
			|| data->map[render->map_y][render->map_x] == 'H')
			handle_secret_door(data, render, ray);
		render->blockdist++;
	}
	if (render->side == 0)
		render->dist_wall = (render->map_x - data->player->x +
								(1 - render->step_x) / 2) / ray.x;
	else
		render->dist_wall = (render->map_y - data->player->y +
								(1 - render->step_y) / 2) / ray.y;
	data->sprite.dist = render->dist_wall;
}

void		load_line_buffer(t_data *data,
	t_render render, t_ray ray, int **buffer)
{
	t_index		x;
	t_graphic	tex;

	x.i = 0;
	tex.wallx = (render.side == 0) ? data->player->y + render.dist_wall *
			ray.y : data->player->x + render.dist_wall * ray.x;
	tex.wallx = tex.wallx - floor((tex.wallx));
	tex.tex_x = (int)(tex.wallx * render.current.img_width);
	if (render.side == 0 && ray.x > 0)
		tex.tex_x = render.current.img_width - tex.tex_x - 1;
	if (render.side == 1 && ray.y < 0)
		tex.tex_x = render.current.img_width - tex.tex_x - 1;
	tex.step = 1.0f * render.current.img_height / render.lineheight;
	tex.texpos = (render.drawstart - ((data->info->height / 2)) +
		(render.lineheight / 2)) * tex.step;
	x.j = render.drawstart;
	while (x.j++ < render.drawend)
	{
		tex.tex_y = (int)tex.texpos & (render.current.img_height) - 1;
		tex.texpos += tex.step;
		(*buffer)[x.i++] = get_darkness(render.current.add_tex[
			render.current.img_height * tex.tex_y + tex.tex_x],
					render.lineheight);
	}
}

void		side_x(t_render *render)
{
	render->sidedist_x = render->sidedist_x + render->dist_x;
	render->map_x = render->map_x + render->step_x;
	render->side = 0;
}

void		side_y(t_render *render)
{
	render->sidedist_y = render->sidedist_y + render->dist_y;
	render->map_y = render->map_y + render->step_y;
	render->side = 1;
}

void		hit_sprite(t_data *data, t_render *render)
{
	data->sprite.x = render->map_x;
	data->sprite.y = render->map_y;
}
