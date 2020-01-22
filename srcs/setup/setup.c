/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:15:19 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/21 21:47:52 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_data		*malloc_struct(void)
{
	t_data *data;

	if (!(data = malloc(sizeof(t_data))))
		return (0);
	if (!(data->player = malloc(sizeof(t_player))))
		return (0);
	if (!(data->info = malloc(sizeof(t_info))))
		return (0);
	if (!(data->image = malloc(sizeof(t_image))))
		return (0);
	if (!(data->tex = malloc(sizeof(t_texture))))
		return (0);
	initialize_struct_texture(data);
	return (data);
}

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
	data->save = 0;
}
