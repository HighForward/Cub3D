/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:45:46 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/20 11:45:46 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	obstacle(t_data *data, float move)
{
	if (data->map[(int)data->player->y][(int)data->player->x] == '1' ||
		data->map[(int)data->player->y][(int)data->player->x] == 'D' ||
		data->map[(int)data->player->y][(int)data->player->x] == '2' ||
		data->map[(int)data->player->y][(int)data->player->x] == 'H')
	{
		data->player->x += -move * data->player->d.x;
		data->player->y += -move * data->player->d.y;
		take_damage(data, 2);
	}
}

void	move_side(t_data *data, float move)
{
	if (data->player->view > 0)
		move = -move;
	rotate_player(data->player, (M_PI / 180) * 90.0f);
	data->player->x += -move * data->player->d.x;
	data->player->y += -move * data->player->d.y;
	obstacle(data, -move);
	rotate_player(data->player, (M_PI / 180) * -90.0f);
}

void	move_front_back(t_data *data, float move)
{
	data->player->x += move * data->player->d.x;
	data->player->y += move * data->player->d.y;
	obstacle(data, move);
}

void	direction(t_vector *v, float angle)
{
	float temp;

	temp = v->x;
	v->x = v->x * cos(angle) - v->y * sin(angle);
	v->y = temp * sin(angle) + v->y * cos(angle);
}

void	rotate_player(t_player *player, float angle)
{
	direction(&player->d, angle);
	direction(&player->p, angle);
}
