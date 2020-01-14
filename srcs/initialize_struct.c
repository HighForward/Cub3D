/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:57:47 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/09 14:39:37 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		initialize_struct_texture(t_data *data)
{
	data->map = NULL;
	data->tex->north.path = NULL;
	data->tex->south.path = NULL;
	data->tex->east.path = NULL;
	data->tex->west.path = NULL;
	data->tex->sprite.path = NULL;
	data->tex->door.path = NULL;
	data->tex->dead.path = NULL;
	data->tex->hud.path = NULL;
	data->info->height = 0;
	data->info->width = 0;
	data->info->color_floor = 0;
	data->info->color_cellar = 0;
	data->player->dead = 0;
	data->sprite.west = 0;
	data->sprite.north = 0;
	data->sprite.est = 0;
	data->sprite.south = 0;
}