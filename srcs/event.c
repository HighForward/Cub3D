/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:07:16 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/14 19:03:17 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int display(t_data *data, int key)
{
	if (display_view(data->player, data) == 0)
		return (0);
	display_hud(data);
	print_map(data);
	display_lifebar(data);
	display_cross(data);
	if (data->player->dead == 1)
		display_dead_screen(data, key);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->image, 0, 0);
	return (1);
}

int     get_event(int key, t_data *data)
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
    	free(data->player);
    	free(data->info);
    	free(data->image);
    	free(data->tex);
    	free_entire_map(data->map);
    	free(data);
		system("leaks a.out");
		exit(1);
	}
    leave_secret_door(data);
    data->secret_key = key == 14 ? 1 : 0;
    if (display(data, key) == 0)
    	exit(1);
    return (1);
}