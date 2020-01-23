/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 03:57:42 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/23 08:03:54 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	setup_sprite(t_data *data, t_ray ray, t_render_sprite *r)
{
	r->pos_x = data->sprite.x - data->player->x;
	r->pos_y = data->sprite.y - data->player->y;
	r->view = 1.0 / (data->player->p.x * data->player->d.y -
		data->player->d.x * data->player->p.y);
	r->ech_x = r->view * (data->player->d.y *
		r->pos_x - data->player->d.x * r->pos_y);
	r->ech_y = r->view * (-data->player->p.y *
		r->pos_x + data->player->p.x * r->pos_y);
	r->line_x = (int)(data->info->width / 2) * (1 + r->ech_x / r->ech_y);
	r->height = abs((int)(data->info->height / (r->ech_y))) / 1;
	r->width = abs((int)(data->info->height / (r->ech_y))) / 1;
	r->s_y = -r->height / 2 + data->info->height / 2;
}

void	setup_pixel_sprite(t_data *data, t_ray ray, t_render_sprite *r)
{
	if (r->s_y < 0)
		r->s_y = 0;
	r->e_y = r->height / 2 + data->info->height / 2;
	if (r->e_y >= data->info->height)
		r->e_y = data->info->height - 1;
	r->s_x = -r->width / 2 + r->line_x;
	if (r->s_x < 0)
		r->s_x = 0;
	r->e_x = r->width / 2 + r->line_x;
	if (r->e_x >= data->info->width)
		r->e_x = data->info->width - 1;
	if (r->width == 0)
		r->width = 1;
}

void	display_sprite(t_data *data, t_ray ray)
{
	t_render_sprite r;

	setup_sprite(data, ray, &r);
	setup_pixel_sprite(data, ray, &r);
	r.tex_x = (int)((32 * (ray.i - (-r.width / 2 + r.line_x)) *
		data->tex->sprite.img_width / r.width) / 32);
	if (r.ech_y > 0 && ray.i > 0 && ray.i < data->info->width &&
		r.ech_y <= data->sprite.dist)
	{
		while (r.s_y < r.e_y)
		{
			r.d = (r.s_y) * 32 - data->info->height * 16 + r.height * 16;
			r.tex_y = ((r.d * data->tex->sprite.img_height) / r.height) / 32;
			r.color = data->tex->sprite.add_tex[data->tex->sprite.img_width
				* r.tex_y + r.tex_x];
			if (r.tex_x < 0 || r.tex_x > 31)
				return ;
			if (r.color != convertrgb(0, 0, 0) && r.tex_x > 0)
				data->image->img_data[(r.s_y + data->info->shift)
				* data->info->width + ray.i] =
					r.color;
			r.s_y++;
		}
	}
}
