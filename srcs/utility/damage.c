/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:04:46 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/23 07:45:43 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	take_damage(t_data *data, int value)
{
	int j;
	int i;

	j = 0;
	data->player->life -= value;
	if (data->player->life <= 0)
	{
		data->player->life = 100;
		data->player->x = data->player->spawn.spawn_x + 0.20f;
		data->player->y = data->player->spawn.spawn_y + 0.20f;
		data->player->dead = 1;
	}
}
