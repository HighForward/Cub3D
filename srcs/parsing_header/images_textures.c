/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 08:31:43 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/20 11:49:23 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			create_image(t_data *data)
{
	int bpp;
	int size_line;
	int endian;

	bpp = 8;
	data->image->image = mlx_new_image(data->mlx_ptr, data->info->width,
			data->info->height);
	data->image->img_data = (int *)mlx_get_data_addr(data->image->image,
			&bpp, &size_line, &endian);
	return (1);
}

int			fill_textures(t_data *data, t_tex_info *tex_info)
{
	int bpp;
	int size_line;
	int endian;

	if (!(tex_info->data_tex = mlx_xpm_file_to_image(data->mlx_ptr,
			tex_info->path, &tex_info->img_width, &tex_info->img_height)))
		return (return_string(0, "Error\n"));
	if (!(tex_info->add_tex = (int *)mlx_get_data_addr(tex_info->data_tex,
			&bpp, &size_line, &endian)))
		return (return_string(0, "Error\n"));
	free(tex_info->path);
	tex_info->path = NULL;
	return (1);
}

int			load_texture(t_data *data)
{
	if (!(fill_textures(data, &data->tex->north)))
		return (0);
	if (!(fill_textures(data, &data->tex->south)))
		return (0);
	if (!(fill_textures(data, &data->tex->west)))
		return (0);
	if (!(fill_textures(data, &data->tex->east)))
		return (0);
	if (!(fill_textures(data, &data->tex->sprite)))
		return (0);
	if (!(fill_textures(data, &data->tex->door)))
		return (0);
	if (!(fill_textures(data, &data->tex->dead)))
		return (0);
	if (!(fill_textures(data, &data->tex->hud)))
		return (0);
	return (1);
}
