/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:17:11 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/22 00:56:23 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_full_screen(int *dest1, int *dest2)
{
	*dest2 = *dest2 < 500 ? 500 : *dest2;
	*dest1 = *dest1 < 500 ? 500 : *dest1;
	*dest2 = *dest2 > 2560 ? 2560 : *dest2;
	*dest1 = *dest1 > 1400 ? 1400 : *dest1;
	*dest2 = *dest2 < *dest1 ? *dest1 : *dest2;
}

int		parse_map_info_window(char *str, int *dest1, int *dest2, int start)
{
	char	*temp;
	int		i;
	int		space;

	*dest1 = 0;
	*dest2 = 0;
	i = 0;
	temp = &str[start];
	if (temp[i] >= '0' && temp[i] <= '9')
		*dest2 = get_value_window(&temp[i], &i);
	else
		return (0);
	if ((space = skip_space(&temp[i])) > 0)
		i = i + space;
	else
		return (0);
	if (temp[i] >= '0' && temp[i] <= '9')
		*dest1 = get_value_window(&temp[i], &i);
	else
		return (0);
	if (ft_isprint(temp[i]))
		return (0);
	check_full_screen(dest1, dest2);
	return (1);
}

int		parse_info_textures(char *s, t_data *data)
{
	if (ft_strnstr(s, "NO ", 3) && data->tex->north.path == NULL)
		data->tex->north.path = ft_strdup(s + 2 + skip_space(s + 2));
	else if (ft_strnstr(s, "SO ", 3) && data->tex->south.path == NULL)
		data->tex->south.path = ft_strdup(s + 2 + skip_space(s + 2));
	else if (ft_strnstr(s, "WE ", 3) && data->tex->west.path == NULL)
		data->tex->west.path = ft_strdup(s + 2 + skip_space(s + 2));
	else if (ft_strnstr(s, "EA ", 3) && data->tex->east.path == NULL)
		data->tex->east.path = ft_strdup(s + 2 + skip_space(s + 2));
	else if (ft_strnstr(s, "S ", 2) && data->tex->sprite.path == NULL)
		data->tex->sprite.path = ft_strdup(s + 1 + skip_space(s + 1));
	else if (ft_strnstr(s, "D ", 2) && data->tex->door.path == NULL)
		data->tex->door.path = ft_strdup(s + 1 + skip_space(s + 1));
	else if (ft_strnstr(s, "DEAD ", 5) && data->tex->dead.path == NULL)
		data->tex->dead.path = ft_strdup(s + 4 + skip_space(s + 4));
	else if (ft_strnstr(s, "HUD ", 4) && data->tex->hud.path == NULL)
		data->tex->hud.path = ft_strdup(s + 3 + skip_space(s + 3));
	return (1);
}

int		parse_info_c_f(char *s, t_data *data)
{
	if (ft_strnstr(s, "F ", 2) && data->info->color_floor == 0)
	{
		if ((get_texture_c_f(s, 1 + skip_space(s + 1),
			&data->info->color_floor)) == 0)
			return (-1);
	}
	else if (ft_strnstr(s, "C ", 2) && data->info->color_cellar == 0)
	{
		if ((get_texture_c_f(s, 1 + skip_space(s + 1),
			&data->info->color_cellar)) == 0)
			return (-1);
	}
	return (1);
}

int		get_texture_c_f(char *str, int i, int *color)
{
	t_color temp_color;

	if (str[i] >= '0' && str[i] <= '9')
	{
		temp_color.rgba.r = get_value_window(&str[i], &i);
		if (skip_space_virgule(&str[i], &i) > 0)
		{
			if (str[i] >= '0' && str[i] <= '9')
			{
				temp_color.rgba.g = get_value_window(&str[i], &i);
				if (skip_space_virgule(&str[i], &i) > 0)
				{
					if (str[i] >= '0' && str[i] <= '9')
					{
						temp_color.rgba.b = get_value_window(&str[i], &i);
						(*color) = temp_color.value;
						if (!ft_isprint(str[i]))
							return (1);
					}
				}
			}
		}
	}
	return (0);
}
