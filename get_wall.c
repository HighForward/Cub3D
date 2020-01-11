/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:07:22 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/10 14:04:16 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int    display_view(t_player *p, t_data *data)
{
    float camera;
    t_ray ray;

    ray.i = 0;
    while (ray.i < data->info->width)
    {
        camera = 2.0f * ray.i / data->info->width - 1.0f;
        ray.x = data->player->d.x + data->player->p.x * camera;
        ray.y = data->player->d.y + data->player->p.y * camera;
        if (get_wall(data, ray) == 0)
        	return (0);
        ray.i++;
    }
    return (1);
}

t_tex_info	current_texture(t_data *data, t_render render)
{
	if (render.side == 1 && render.step_y == 1 && render.secret_door != 1)
		return (data->tex->north);
	else if (render.side == 1 && render.step_y == -1 && render.secret_door != 1)
		return (data->tex->south);
	else if (render.side == 0 && render.step_x == -1 && render.secret_door != 1)
		return (data->tex->east);
	else if (render.side == 0 && render.step_x == 1 && render.secret_door != 1)
		return (data->tex->west);
	else
		return (data->tex->door);
}

void    load_line_buffer(t_data *data, t_render render, t_ray ray, t_line size, t_tex_info current, int **buffer)
{
    int y;
    int i;
    t_graphic line;

    i = 0;
    if (render.side == 0)
        line.wallX = data->player->y + render.perpWallDist * ray.y;
    else
        line.wallX = data->player->x + render.perpWallDist * ray.x;
    line.wallX = line.wallX - floor((line.wallX));
    line.texX = (int)(line.wallX * current.img_width);
    if (render.side == 0 && ray.x > 0)
        line.texX = current.img_width - line.texX - 1;
    if (render.side == 1 && ray.y < 0)
        line.texX = current.img_width - line.texX - 1;
    line.step = 1.0f * current.img_height / size.lineHeight;
    line.texPos = (size.drawstart - (data->info->height / 2) + (size.lineHeight / 2)) * line.step;
    y = size.drawstart;
    while (y < size.drawend)
    {
        line.texY = (int)line.texPos & (current.img_height) - 1;
        line.texPos += line.step;
        (*buffer)[i] = current.add_tex[current.img_height * line.texY + line.texX];
        i++;
        y++;
    }
}

void    print_lines(t_data *data, t_line line, t_ray ray, int *buffer)
{
    line.i = 0;
    line.x = 0;
    while (line.x < data->info->height)
    {
        if (line.x >= line.drawstart && line.x < line.drawend)
        {
            data->image->img_data[line.x * data->info->width + ray.i] = buffer[line.i];;
            line.i++;
        }
        else if (line.x <= line.drawstart)
        {
            data->image->img_data[line.x * data->info->width + ray.i] = data->info->color_cellar;
        }
        else if (line.x >= line.drawend && line.x < data->info->height)
        {
            data->image->img_data[line.x * data->info->width + ray.i] = data->info->color_floor;
        }
        line.x++;
    }
    free(buffer);
}

int    get_size_line(t_data *data, t_ray ray, t_render render)
{
    int color;
    int *buffer;
    t_line line;

    line.i = 0;
    line.x = 0;
    t_tex_info current;
    current = current_texture(data, render);
    line.drawstart = 0;
    line.drawend = 0;
    line.lineHeight = (int)(data->info->height / render.perpWallDist);
    line.drawstart = (-line.lineHeight / 2 + data->info->height / 2);
    line.drawend = line.lineHeight / 2 + data->info->height / 2;
    if (line.drawstart < 0)
        line.drawstart = 0;
    if (line.drawend >= data->info->height)
        line.drawend = data->info->height - 1;
    buffer = malloc(sizeof(int) * (current.img_height * current.img_width + 1));
    load_line_buffer(data, render, ray, line, current, &buffer);
    print_lines(data, line, ray, buffer);
    return (1);
}

void     get_wall_dda(t_data *data, t_render *render, t_ray ray)
{
    while (render->hit == 0)
    {
        if (render->sideDistX < render->sideDistY)
        {
            render->sideDistX = render->sideDistX + render->deltaDistX;
            render->map_x = render->map_x + render->step_x;
            render->side = 0;
        }
        else
        {
            render->sideDistY = render->sideDistY + render->deltaDistY;
            render->map_y = render->map_y + render->step_y;
            render->side = 1;
        }
        if (data->map[render->map_y][render->map_x] == '1')
            render->hit = 1;
        else if (data->map[render->map_y][render->map_x] == 'D' || data->map[render->map_y][render->map_x] == 'H')
            handle_secret_door(data, render, ray);
        render->blockdist++;
    }
    if (render->side == 0)
        render->perpWallDist = (render->map_x - data->player->x + (1 - render->step_x) / 2) / ray.x;
    else
        render->perpWallDist = (render->map_y - data->player->y + (1 - render->step_y) /2) / ray.y;
}

void    setup_ray_render(t_data *data, t_render *render, t_ray ray)
{
    render->secret_door = 0;
    render->perpWallDist = 0.0f;
    render->blockdist = 0;
    render->hit = 0;
    render->map_x = (int)data->player->x;
    render->map_y = (int)data->player->y;
    render->deltaDistX = sqrt(1 + (ray.y * ray.y) / (ray.x * ray.x));
    render->deltaDistY = sqrt(1 + (ray.x * ray.x) / (ray.y * ray.y));
    render->step_x = ray.x < 0 ? -1 : 1;
    render->step_y = ray.y < 0 ? -1 : 1;
    render->sideDistX = (ray.x < 0 ? data->player->x - render->map_x : render->map_x + 1.0f - data->player->x) * render->deltaDistX;
    render->sideDistY = (ray.y < 0 ? data->player->y - render->map_y : render->map_y + 1.0f - data->player->y) * render->deltaDistY;
}

int     get_wall(t_data *data, t_ray ray)
{
    t_render render;

    setup_ray_render(data, &render, ray);
    get_wall_dda(data, &render, ray);
    get_size_line(data, ray, render);
    return (1);
}
