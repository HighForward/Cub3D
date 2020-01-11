#include "../includes/cub3d.h"

void	put_int_in_char(unsigned char *begin, int val)
{
    begin[0] = (unsigned char)(val);
    begin[1] = (unsigned char)(val >> 8);
    begin[2] = (unsigned char)(val >> 16);
    begin[3] = (unsigned char)(val >> 24);
}

int     bmp_header(int save, int size, t_data *data)
{
    int				index;
    unsigned char	header[54];

    index = 0;
    while (index < 54)
        header[index++] = (unsigned char)(0);
    header[0] = (unsigned char)('B');
    header[1] = (unsigned char)('M');
    put_int_in_char(header + 2, size);
    header[10] = (unsigned char)(54);
    header[14] = (unsigned char)(40);
    put_int_in_char(header + 18, data->info->width);
    put_int_in_char(header + 22, data->info->width);
    header[27] = (unsigned char)(1);
    header[28] = (unsigned char)(24);
    return (!(write(save, header, 54) < 0));
}

int	write_data(int file, t_data *data, int step)
{
    const unsigned char	zero[3] = {0, 0, 0};
    int					x;
    int					y;
    int					color;
    t_color             current;

    y = data->info->height;
    while (y > 0)
    {
        x = 0;
        while (x < data->info->width) // x * data->info->width + ray.i
        {
            current = c(data->image->img_data[x + y * data->info->width]);
            color = current.value;
            if (write(file, &color, 3) < 0)
                return (0);
            if (step > 0 && write(file, &zero, step) < 0)
                return (0);
            x++;
        }
        y--;
    }
    return (1);
}

int     save_bmp(t_data *data)
{
    int save;
    int size;
    save = open("screen.bmp", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    size = 54 + ((data->info->width + 4) * data->info->height);
    bmp_header(save, size, data);
    write_data(save, data, 4);
    close(save);
    return (1);
}