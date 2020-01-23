/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:50:56 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/23 08:12:44 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		close_red_button(t_data *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	system("leaks cub3d");
	return (return_error(1, game, "Successfully closed\n"));
}

int		free_and_return(int value, char *str)
{
	if (str)
		free(str);
	return (value);
}

int		return_string(int value, char *str)
{
	ft_putstr(str);
	return (value);
}

int		return_string_free(int value, char *str)
{
	ft_putstr(str);
	if (str)
		free(str);
	ft_putstr("\n");
	return (value);
}

int		return_error(int value, t_data *data, char *str)
{
	if (data->tex->north.path != NULL)
		free(data->tex->north.path);
	if (data->tex->south.path != NULL)
		free(data->tex->south.path);
	if (data->tex->east.path != NULL)
		free(data->tex->east.path);
	if (data->tex->west.path != NULL)
		free(data->tex->west.path);
	if (data->tex->door.path != NULL)
		free(data->tex->door.path);
	if (data->tex->sprite.path != NULL)
		free(data->tex->sprite.path);
	if (data->tex->dead.path != NULL)
		free(data->tex->dead.path);
	if (data->tex->hud.path != NULL)
		free(data->tex->hud.path);
	if (data->map != NULL)
		free_entire_map(data->map);
	ft_putstr(str);
	free(data->tex);
	free(data->player);
	free(data->image);
	free(data->info);
	exit(0);
}
