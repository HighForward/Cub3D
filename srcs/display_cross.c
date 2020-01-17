/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_cross.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:08:15 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/09 16:36:56 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int display_cross_around(t_data *data, int color)
{
	data->image->img_data[(data->info->height / 2) * data->info->width + (data->info->width / 2)] = color;
	data->image->img_data[(data->info->height / 2 + 15) * data->info->width + (data->info->width / 2)] = color;
	data->image->img_data[(data->info->height / 2 - 15) * data->info->width + (data->info->width / 2)] = color;
	data->image->img_data[(data->info->height / 2) * data->info->width + ((data->info->width / 2) + 15)] = color;
	data->image->img_data[(data->info->height / 2) * data->info->width + ((data->info->width / 2) - 15)] = color;
	data->image->img_data[(data->info->height / 2 + 16) * data->info->width + (data->info->width / 2)] = color;
	data->image->img_data[(data->info->height / 2 - 16) * data->info->width + (data->info->width / 2)] = color;
	data->image->img_data[(data->info->height / 2) * data->info->width + ((data->info->width / 2) + 16)] = color;
	data->image->img_data[(data->info->height / 2) * data->info->width + ((data->info->width / 2) - 16)] = color;
	data->image->img_data[(data->info->height / 2 + 14) * data->info->width + (data->info->width / 2)] = color;
	data->image->img_data[(data->info->height / 2 - 14) * data->info->width + (data->info->width / 2)] = color;
	data->image->img_data[(data->info->height / 2) * data->info->width + ((data->info->width / 2) + 14)] = color;
	data->image->img_data[(data->info->height / 2) * data->info->width + ((data->info->width / 2) - 14)] = color;
	return (1);
}

int display_cross_pixel(int x, int y, t_data *data, int color)
{
	data->image->img_data[((data->info->height / 2) + x) * data->info->width + ((data->info->width / 2) + y)] = color;
	data->image->img_data[((data->info->height / 2) + y) * data->info->width + ((data->info->width / 2) + x)] = color;
	data->image->img_data[((data->info->height / 2) - x) * data->info->width + ((data->info->width / 2) + y)] = color;
	data->image->img_data[((data->info->height / 2) - y) * data->info->width + ((data->info->width / 2) + x)] = color;
	data->image->img_data[((data->info->height / 2) + x) * data->info->width + ((data->info->width / 2) - y)] = color;
	data->image->img_data[((data->info->height / 2) + y) * data->info->width + ((data->info->width / 2) - x)] = color;
	data->image->img_data[((data->info->height / 2) - x) * data->info->width + ((data->info->width / 2) - y)] = color;
	data->image->img_data[((data->info->height / 2) - y) * data->info->width + ((data->info->width / 2) - x)] = color;
	return (1);
}


int display_cross_circle(int x, int y, t_data *data, int color)
{
	int d;

	d = y - 1;
	while (y >= x)
	{
		display_cross_pixel(x, y, data, color);
		if (d >= 2 * x)
		{
			d -= 2 * x + 1;
			x++;
		} else if (d < 2 * (5 - y))
		{
			d += 2 * y - 1;
			y--;
		} else
		{
			d += 2 * (y - x - 1);
			y--;
			x++;
		}
	}
	return (1);
}

int display_cross(t_data *data)
{
	display_cross_circle(0, 5, data, convertRGB(255, 255, 255));
	display_cross_circle(10, 5, data, convertRGB(255, 255, 255));
	display_cross_circle(0, 6, data, convertRGB(0, 0, 0));
	display_cross_circle(0, 4, data, convertRGB(0, 0, 0));
	display_cross_circle(0, 1, data, convertRGB(0, 0, 0));
	display_cross_around(data, convertRGB(255, 255, 0));
	return (1);
}