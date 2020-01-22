/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:35:41 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/21 21:35:41 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_orientation(t_data *data, t_vector d, t_vector p)
{
	data->player->d = d;
	data->player->p = p;
}

void	set_position(t_data *data, t_index x,
	float step_player, int *player_there)
{
	if (data->map[x.j][x.i] == 'W')
		get_orientation(data, vec(-1.0f, 0.0f), vec(0.0f, -0.6f));
	if (data->map[x.j][x.i] == 'N')
		get_orientation(data, vec(0.0f, -1.0f), vec(0.6f, 0.0f));
	if (data->map[x.j][x.i] == 'S')
		get_orientation(data, vec(0.0f, 1.0f), vec(-0.6f, 0.0f));
	if (data->map[x.j][x.i] == 'E')
		get_orientation(data, vec(1.0f, 0.0f), vec(0.0f, 0.6f));
	data->player->view = VIEW;
	data->player->move = step_player;
	data->player->x = x.i + 0.49;
	data->player->y = x.j + 0.49;
	data->player->spawn = vec_s(x.i, x.j);
	data->player->life = 100;
	(*player_there)++;
}

int		get_position(t_data *data)
{
	t_index		x;
	float		step_player;
	int			player_there;

	player_there = 0;
	step_player = STEP > 1.0f ? 1.0f : STEP;
	x.j = 0;
	while (data->map[x.j])
	{
		x.i = 0;
		while (data->map[x.j][x.i])
		{
			if (data->map[x.j][x.i] == 'W' || data->map[x.j][x.i] == 'E' ||
				data->map[x.j][x.i] == 'N' || data->map[x.j][x.i] == 'S')
				set_position(data, x, step_player, &player_there);
			x.i++;
		}
		x.j++;
	}
	if (player_there != 1)
		return (return_string(0, "Error\nWrong Player location\n"));
	return (1);
}
