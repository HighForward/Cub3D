/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:07:16 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/10 14:20:17 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int display(t_data *data)
{
	if (display_view(data->player, data) == 0)
		return (0);
	print_map(data);
	display_lifebar(data);
	display_cross(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->image, 0, 0);
	return (1);
}

int     get_event(int key, t_data *data)
{
    if (key == 65361)
        rotate_player(data->player, (M_PI / 180) * -data->player->view);
    if (key == 65363)
        rotate_player(data->player, (M_PI / 180) * data->player->view);
    if (key == 122)
        move_front_back(data, data->player->move);
    if (key == 115)
        move_front_back(data, -data->player->move);
    if (key == 113)
        move_side(data, data->player->move);
    if (key == 100)
        move_side(data, -data->player->move);
    if (key == 65307)
		exit(1);
    leave_secret_door(data);
    data->secret_key = key == 101 ? 1 : 0;
    if (display(data) == 0)
    	return (0);
    return (1);
}