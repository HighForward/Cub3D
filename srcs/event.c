/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:43:28 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/23 08:11:35 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		display(t_data *data, int key)
{
	if (display_view(data->player, data) == 0)
		return (0);
	display_hud(data);
	print_map(data);
	display_dir_map(data);
	display_lifebar(data);
	display_cross(data);
	if (data->player->dead == 1)
		display_dead_screen(data, key);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
							data->image->image, 0, 0);
	return (1);
}

int		get_event(int key, t_data *data)
{
	if (key == 123)
		rotate_player(data->player, (M_PI / 180) * -data->player->view);
	if (key == 124)
		rotate_player(data->player, (M_PI / 180) * data->player->view);
	if (key == 13)
		move_front_back(data, data->player->move);
	if (key == 1)
		move_front_back(data, -data->player->move);
	if (key == 0)
		move_side(data, -data->player->move);
	if (key == 2)
		move_side(data, data->player->move);
	if (key == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		return (return_error(0, data, "Game close successfully\n"));
	}
	leave_secret_door(data);
	data->secret_key = key == 14 ? 1 : 0;
	data->info->shift = key == 256 ? -(data->info->height / 4) : 0;
	if (key == 49)
		data->player->dead = 0;
	if (display(data, key) == 0)
		exit(1);
	return (1);
}
