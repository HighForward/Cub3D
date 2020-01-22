/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 23:19:11 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/21 23:23:16 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	display_dead_screen(t_data *data, int key)
{
	t_vector	ech;
	t_vector	step;
	int			i;
	int			j;

	ech.x = (float)data->tex->dead.img_width / (float)data->info->width;
	ech.y = (float)data->tex->dead.img_height / (float)data->info->height;
	step.y = 0;
	i = 0;
	while (i < data->info->height)
	{
		j = 0;
		step.x = 0;
		while (j < data->info->width)
		{
			data->image->img_data[i * data->info->width + j] =
				data->tex->dead.add_tex[((int)step.y) *
				data->tex->dead.img_width + ((int)step.x)];
			step.x += ech.x;
			j++;
		}
		step.y += ech.y;
		i++;
	}
}

void	display_hud(t_data *data)
{
	t_vector	ech;
	t_vector	step;
	int			i;
	int			j;

	ech.x = (float)data->tex->hud.img_width / (float)data->info->width;
	ech.y = (float)data->tex->hud.img_height / (float)data->info->height;
	step.y = 0;
	i = 0;
	while (i < data->info->height)
	{
		j = 0;
		step.x = 0;
		while (j++ < data->info->width)
		{
			if (data->tex->hud.add_tex[((int)step.y) * data->tex->hud.img_width
				+ ((int)step.x)] != convertrgb(255, 0, 0))
				data->image->img_data[i * data->info->width + j - 1] =
				data->tex->hud.add_tex[((int)step.y) *
				data->tex->hud.img_width + ((int)step.x)];
			step.x += ech.x;
		}
		step.y += ech.y;
		i++;
	}
}
