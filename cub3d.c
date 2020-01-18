/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:59:33 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/18 11:58:09 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int wrong_extention(char *str)
{
	int len;

	if ((len = ft_strlen(str)) <= 4)
		return (0);
	if (ft_strnstr(str + len - 4, ".cub", 4) == NULL)
		return (0);
	return (1);
}

int open_file_description(t_data *data, int *fd, char *str)
{
	if (!(wrong_extention(str)))
		return (return_error(0, data, "Error\nWrong map extention\n"));
	if (!((*fd) = open(str, O_RDONLY)))
		return (return_error(0, data, "Error\n"));
	return (1);
}

t_data	*malloc_struct(void)
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

int main(int argc, char **argv)
{
	t_data *data;
	int fd;

	if (!(data = malloc_struct()))
		return (return_error(1, data, "Can't allocate memory\n"));
	if (argc < 2 || argc > 3)
		return (return_error(1, data, "Bad arguments\n"));
	if (!(open_file_description(data, &fd, argv[1])))
		return (return_error(1, data, "Can't open map\n"));
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
	display(data, 0);
	if (argc == 3 && ft_strnstr(argv[2], "-save", 5))
		save_bmp(data);
	else if (argc == 3)
		return (return_error(1, data, "Undefinded parameter\n"));
	mlx_hook(data->win_ptr, 17, 1L << 0, close_red_button, (void *) data);
	mlx_hook(data->win_ptr, 2, 1L << 0, get_event, (void *) data);
	mlx_loop(data->mlx_ptr);
}
