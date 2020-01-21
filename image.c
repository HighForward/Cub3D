#include "includes/cub3d.h"

void display_sprite(t_data *data, t_ray ray)
{
	int dist;
	double spriteX;
	double spriteY;

	double invDet;
	double transformX;
	double transformY;
	int spriteScreenX;
	int spriteHeight;
	int spriteWidth;
	int drawStartY;
	int drawEndY;
	int drawStartX;
	int drawEndX;
	int stripe;
	int texX;
	int texY;
	int d;
	int color;
	int vMoveScreen;
	int x;
	int y;
	int i;

	x = data->sprite.x;
	y = data->sprite.y;
	dist = ((data->player->x - x) * (data->player->x - x) + (data->player->y - y) * (data->player->y - y));
	spriteX = x - data->player->x;
	spriteY = y - data->player->y;
	invDet = 1.0 / (data->player->p.x * data->player->d.y - data->player->d.x * data->player->p.y);
	transformX = invDet * (data->player->d.y * spriteX - data->player->d.x * spriteY);
	transformY = invDet * (-data->player->p.y * spriteX + data->player->p.x * spriteY);
	vMoveScreen = (int) (0.64 / transformY);
	spriteScreenX = (int) (data->info->width / 2) * (1 + transformX / transformY);
	spriteHeight = abs((int) (data->info->height / (transformY))) / 1;
	spriteWidth = abs((int) (data->info->height / (transformY))) / 1;
	drawStartY = -spriteHeight / 2 + data->info->height / 2;
	if (drawStartY < 0)
		drawStartY = 0;
	drawEndY = spriteHeight / 2 + data->info->height / 2;
	if (drawEndY >= data->info->height)
		drawEndY = data->info->height - 1;
	drawStartX = -spriteWidth / 2 + spriteScreenX;
	if (drawStartX < 0)
		drawStartX = 0;
	drawEndX = spriteWidth / 2 + spriteScreenX;
	if (drawEndX >= data->info->width)
		drawEndX = data->info->width - 1;
	stripe = ray.i;
	if (spriteWidth == 0)
		spriteWidth = 1;
	texX = (int) ((32 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * data->tex->sprite.img_width / spriteWidth) /
				  32);
	if (transformY > 0 && stripe > 0 && stripe < data->info->width && transformY <= data->sprite.Perp)
	{
		i = drawStartY;
		while (i < drawEndY)
		{
			d = (i) * 32 - data->info->height * 16 + spriteHeight * 16;
			texY = ((d * data->tex->sprite.img_height) / spriteHeight) / 32;
			color = data->tex->sprite.add_tex[data->tex->sprite.img_width * texY + texX];
			if (texX < 0 || texX > 31)
				return;
			if (color != convertrgb(0, 0, 0) && texX > 0)
				data->image->img_data[i * data->info->width + stripe] = color;
			i++;
		}
	}
}