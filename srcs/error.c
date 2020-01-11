/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:07:34 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/10 14:18:48 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int        close_red_button(t_data *game)
{
	(void)game;
	exit(1);
	return (0);
}

int    free_and_return(int value, char *str)
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

int     return_error(int value, t_data *data, char *str)
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
	if (data->map != NULL)
		free_entire_map(data->map);
    ft_putstr(str);
    //system("leaks a.out");
    return (value);
}