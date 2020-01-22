/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:59:33 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/20 19:12:54 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		function_mlx(t_data *data)
{
	if (data->save == 1)
	{
		save_bmp(data);
		return (return_error(0, data, "Screen saved successfully\n"));
	}
	mlx_hook(data->win_ptr, 17, 1L << 0, close_red_button, (void *)data);
	mlx_hook(data->win_ptr, 2, 1L << 0, get_event, (void *)data);
	mlx_loop(data->mlx_ptr);
	return (1);
}

int		main(int argc, char **argv)
{
	t_data	*data;
	int		fd;

	if (!(data = malloc_struct()))
		return (return_error(1, data, "Can't allocate memory\n"));
	if (!handle_args(data, argv, argc))
		return (return_error(1, data, "Bad arguments\n"));
	if (!(open_file_description(data, &fd, argv[1])))
		return (return_error(1, data, "Can't open map\n"));
	if ((data->mlx_ptr = mlx_init()) == NULL)
		return (return_error(1, data, "Can't init mlx\n"));
	if (!(info_header_cub(fd, data)))
		return (return_error(1, data, "Parsing Header\n"));
	if (!(load_texture(data)))
		return (return_error(1, data, "Cant load textures\n"));
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->info->width, data->info->height, "Cub3D")))
		return (return_error(1, data, "Can't create window\n"));
	if ((create_image(data)) == 0)
		return (return_error(1, data, "Error images\n"));
	if (!(check_map(fd, data)))
		return (return_error(1, data, "Parsing map\n"));
	if (!(display(data, 0)))
		return (return_error(1, data, "Error\nRendering\n"));
	function_mlx(data);
}
