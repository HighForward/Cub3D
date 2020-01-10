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
    float x;
    float y;
    float camera;
    t_ray ray;

    ray.i = 0;
    x = p->x;
    y = p->y;
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

int    print_line(t_data *data, t_ray ray, t_render render)
{
    int color;
    int lineHeight;
    int drawstart;
    int drawend;
    int x;

    drawstart = 0;
    drawend = 0;

    lineHeight = (int)(data->info->height / render.perpWallDist);
    drawstart = (-lineHeight / 2 + data->info->height / 2);
    drawend = lineHeight / 2 + data->info->height / 2;
    if (drawstart < 0)
        drawstart = 0;

    if (drawend >= data->info->height)
        drawend = data->info->height - 1;




    float   wallX;
    int     texX;
    float   step;
    float   texPos;
    int texY;
    int y;
    int buffer[128 * 128 + 1];
    int i;

    t_tex_info current;
    current = current_texture(data, render);
    i = 0;
    if (render.side == 0)
        wallX = data->player->y + render.perpWallDist * ray.y;
    else
        wallX = data->player->x + render.perpWallDist * ray.x;
    wallX = wallX - floor((wallX));
    texX = (int)(wallX * current.img_width);
    if (render.side == 0 && ray.x > 0)
        texX = current.img_width - texX - 1;
    if (render.side == 1 && ray.y < 0)
        texX = current.img_width - texX - 1;

    step = 1.0f * current.img_height / lineHeight;
    texPos = (drawstart - (data->info->height / 2) + (lineHeight / 2)) * step;
    y = drawstart;
    while (y < drawend)
    {
        texY = (int)texPos & (current.img_height) - 1;
        texPos += step;
        buffer[i] = current.add_tex[current.img_height * texY + texX];
        i++;
        y++;
    }


    i = 0;
    x = 0;
    while (x < data->info->height)
    {
        if (x >= drawstart && x < drawend)
        {
            color = buffer[i];
            data->image->img_data[x * data->info->width + ray.i] = color;
            i++;
        }
        else if (x <= drawstart)
        {
            data->image->img_data[x * data->info->width + ray.i] = data->info->color_cellar;
        }
        else if (x >= drawend && x < data->info->height)
        {
            data->image->img_data[x * data->info->width + ray.i] = data->info->color_floor;
        }
        x++;
    }
    //free(buffer);
    return (1);
}

int     get_wall(t_data *data, t_ray ray)
{
    t_render render;

    render.secret_door = 0;
    render.perpWallDist = 0.0f;
    render.blockdist = 0;
    render.hit = 0;
    render.map_x = (int)data->player->x;
    render.map_y = (int)data->player->y;
    render.deltaDistX = sqrt(1 + (ray.y * ray.y) / (ray.x * ray.x));
    render.deltaDistY = sqrt(1 + (ray.x * ray.x) / (ray.y * ray.y));
    render.step_x = ray.x < 0 ? -1 : 1;
    render.step_y = ray.y < 0 ? -1 : 1;
    render.sideDistX = (ray.x < 0 ? data->player->x - render.map_x : render.map_x + 1.0f - data->player->x) * render.deltaDistX;
    render.sideDistY = (ray.y < 0 ? data->player->y - render.map_y : render.map_y + 1.0f - data->player->y) * render.deltaDistY;
    while (render.hit == 0)
    {
        if (render.sideDistX < render.sideDistY)
        {
            render.sideDistX = render.sideDistX + render.deltaDistX;
            render.map_x = render.map_x + render.step_x;
            render.side = 0;
        }
        else
        {
            render.sideDistY = render.sideDistY + render.deltaDistY;
            render.map_y = render.map_y + render.step_y;
            render.side = 1;
        }
        if (data->map[render.map_y][render.map_x] == '1')
            render.hit = 1;
        else if (data->map[render.map_y][render.map_x] == 'D' || data->map[render.map_y][render.map_x] == 'H')
            handle_secret_door(data, &render, ray);
        render.blockdist++;
    }
    if (render.side == 0)
        render.perpWallDist = (render.map_x - data->player->x + (1 - render.step_x) / 2) / ray.x;
    else
        render.perpWallDist = (render.map_y - data->player->y + (1 - render.step_y) /2) / ray.y;
    if (print_line(data, ray, render) == 0)
    	return (0);
    return (1);
}
