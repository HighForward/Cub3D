/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:07:41 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/09 16:30:55 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int main(int argc, char **argv)
{
    t_data *data;
    int fd;

    data = malloc(sizeof(t_data));
    data->player = malloc(sizeof(t_player));
    data->info = malloc(sizeof(t_info));
    data->image = malloc(sizeof(t_image));
    data->tex = malloc(sizeof(t_texture));
	initialize_struct_texture(data);
    if (argc > 3 || argc < 2)
        return (return_error(1, data, "Bad arguments\n"));
    if (!(fd = open(argv[1], O_RDONLY)))
        return (return_error(1, data, "Can't open map"));
    if ((data->mlx_ptr = mlx_init()) == NULL)
        return (return_error(1, data, "Can't init mlx\n"));
    if (!(info_header_cub(fd, data)))
        return (return_error(1, data, "Parsing Header\n"));
    if (!(load_texture(data)))
        return (return_error(1, data, "Cant load textures\n"));
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, data->info->width, data->info->height, "Cub3D")))
		return (return_error(1, data, "Can't create window\n"));
	if ((create_image(data)) == 0)
		return (return_error(1, data, "Error images\n"));
    if (!(check_map(fd, data)))
        return (return_error(1, data, "Parsing map\n"));
	display(data);
    mlx_hook(data->win_ptr, 17, 1L << 0, close_red_button, (void*)data);
    mlx_hook(data->win_ptr, 2, 1L << 0, get_event, (void*)data);
    mlx_loop(data->mlx_ptr);
    return (0);
}