/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 23:29:53 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/21 23:29:53 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		display_lifebar_bar(t_data *data)
{
	int		width_lifebar;
	int		start;
	int		x;
	int		temp_start;
	float	percentage;

	x = data->info->height - 50;
	start = data->info->width / 3;
	temp_start = start;
	width_lifebar = data->info->width / 3;
	percentage = (width_lifebar / 100) * (100 - data->player->life);
	while (x < data->info->height - 10)
	{
		start = data->info->width / 3;
		while (start < (width_lifebar + temp_start) - percentage)
		{
			data->image->img_data[x * data->info->width + start] =
					degrade_couleur(convertrgb(255, 0, 0), start / 10);
			start++;
		}
		x++;
	}
	return (1);
}

int		display_lifebar(t_data *data)
{
	int		width_lifebar;
	int		start;
	int		x;
	int		temp_start;
	float	percentage;

	x = data->info->height - 60;
	start = data->info->width / 3;
	temp_start = start;
	width_lifebar = data->info->width / 3;
	percentage = (width_lifebar / 100) * (100 - data->player->life);
	while (x < data->info->height)
	{
		start = (data->info->width / 3) - 10;
		while (start < width_lifebar + temp_start + 10)
		{
			data->image->img_data[x * data->info->width + start] =
					convertrgb(0, 0, 0);
			start++;
		}
		x++;
	}
	display_lifebar_bar(data);
	return (1);
}
