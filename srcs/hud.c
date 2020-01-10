#include "../includes/cub3d.h"

int     display_lifebar(t_data *data)
{
    int width_lifebar;
    int start;
    int x;
    int temp_start;
    float percentage;

    x = data->info->height - 60;
    start = data->info->width / 4;
    temp_start = start;
    width_lifebar = data->info->width / 2;
    percentage = (width_lifebar / 100) * (100 - data->player->life);

    while (x < data->info->height)
    {
        start = (data->info->width / 4) - 10;
        while (start < width_lifebar + temp_start + 10)
        {
            data->image->img_data[x * data->info->width + start] = convertRGB(0, 0, 0);
            start++;
        }
        x++;
    }
    x = data->info->height - 50;
    while (x < data->info->height - 10)
    {
        start = data->info->width / 4;
        while (start < (width_lifebar + temp_start) - percentage)
        {
            data->image->img_data[x * data->info->width + start] = convertRGB(255, 0, 0);
            start++;
        }
        x++;
    }
    return (1);
}

int     get_transparency(t_data *data, int source, int destination)
{
    float one;
    float two;
    float result;

    one = (127 * source) / 255;
    two = ((255 - 127) * destination) / 255;
    result = one + two;
    return (result);
}

void    display_rekt(int x, int y, int color, t_data *data)
{
    int i;
    int j;
    int count;
    t_color w;
    t_color z;
    t_color final;

    count = 1;
    i = x;
    j = y;
    while (x < i + ((data->info->width + data->info->height) / 200))
    {
        y = j;
        while (y < j + ((data->info->width + data->info->height) / 200))
        {
			w = c(color);
			z = c(data->image->img_data[y * data->info->width + x]);
            final.rgba.r = get_transparency(data, w.rgba.r, z.rgba.r);
            final.rgba.g = get_transparency(data, w.rgba.g, z.rgba.g);
            final.rgba.b = get_transparency(data, w.rgba.b, z.rgba.b);
            data->image->img_data[y * data->info->width + x] = final.value;
            y++;
        }
        x++;
    }
}

void    ft_putpixel(char *line, int i, t_data *data)
{
    int x;
    int y;
    int index;
    int color;
    int j;

    index = 0;
    x = 0;
    y = (i * ((data->info->width + data->info->height) / 200));

    while (line[index])
    {
        if (line[index] == '1')
            color = convertRGB(0, 0, 0);
        else if (line[index] == 'D')
            color = convertRGB(170, 170, 170);
        else if (line[index] == 'H')
            color = convertRGB(153, 0, 110);
        else if (line[index] == '2')
            color = convertRGB(25, 25, 25);
		else if (index == (int)data->player->x && i == (int)data->player->y)
			color = convertRGB(255, 255, 255);
        else
            color = convertRGB(255, 0, 0);
        display_rekt(x, y, color, data);
        x += ((data->info->width + data->info->height) / 200);
        index++;
    }
}

void    print_map(t_data *data)
{
    int i;

    i = 0;
    while (data->map[i])
    {
        ft_putpixel(data->map[i], i, data);
        i++;
    }
}