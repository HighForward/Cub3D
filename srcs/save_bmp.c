#include "../includes/cub3d.h"

void put_int_in_char(unsigned char *begin, int val)
{
	begin[0] = (unsigned char) (val);
	begin[1] = (unsigned char) (val >> 8);
	begin[2] = (unsigned char) (val >> 16);
	begin[3] = (unsigned char) (val >> 24);
}

int bmp_header(int save, int size, t_data *data)
{
	int index;
	unsigned char header[54];

	index = 0;
	while (index < 54)
		header[index++] = (unsigned char) (0);
	header[0] = (unsigned char) ('B');
	header[1] = (unsigned char) ('M');
	put_int_in_char(header + 2, size);
	header[10] = (unsigned char) (54);
	header[14] = (unsigned char) (40);
	put_int_in_char(header + 18, data->info->width);
	put_int_in_char(header + 22, data->info->height);
	header[27] = (unsigned char) (1);
	header[28] = (unsigned char) (24);
	return (!(write(save, header, 54) < 0));
}

int write_data(int file, t_data *data)
{
	int x;
	int y;
	int color;

	y = data->info->height;
	while (y > 0)
	{
		x = 0;
		while (x < data->info->width)
		{
			color = data->image->img_data[y * data->info->width + x];
			if (write(file, &color, 3) < 0)
				return (0);
			x++;
		}
		y--;
	}
	return (1);
}

int save_bmp(t_data *data)
{
	int save;
	int size;
	if (!(save = open("screen.bmp", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR)))
		return (return_string(0, "Can't load screen.bmp"));
	size = 54 + (((int) data->info->width) * (int) data->info->height);
	bmp_header(save, size, data);
	write_data(save, data);
	close(save);
	return (1);
}