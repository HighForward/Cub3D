/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 08:14:07 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/10 11:39:35 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct 	s_sprite
{
	int x;
	int y;
	int north;
	int south;
	int west;
	int est;
}				t_sprite;

typedef struct  s_line
{
    int lineHeight;
    int drawstart;
    int drawend;
    int x;
    int i;
}               t_line;

typedef struct  s_graphic
{
    float   wallX;
    int     texY;
    int     texX;
    float   step;
    float   texPos;
}               t_graphic;

typedef struct  s_info
{
	int height;
	int width;
	char *north;
	char *south;
	char *east;
	char *west;
	char *sprite;
	char *door;
	int color_cellar;
	int color_floor;
}               t_info;

typedef struct  s_ray
{
	float x;
	float y;
	int i;
}               t_ray;

typedef struct  s_spawn_player
{
	int spawn_x;
	int spawn_y;
}               t_spawn_player;

typedef struct  s_vector
{
	float x;
	float y;
}               t_vector;

typedef struct  s_player
{
	int life;
	int dead;
	float x;
	float y;
	float view;
	float move;
	t_vector d;
	t_vector p;
	t_spawn_player spawn;
}               t_player;

typedef struct  s_image
{
	char *image;
	int *img_data;
}               t_image;


typedef struct  s_texture_info
{
	char *path;
	void *data_tex;
	int *add_tex;
	int img_height;
	int img_width;
}               t_tex_info;

typedef struct  s_render
{
	int map_x;
	int map_y;
	float deltaDistX;
	float deltaDistY;
	int step_x;
	int step_y;
	float sideDistX;
	float sideDistY;
	int side;
	int hit;
	int blockdist;
	float perpWallDist;
	int lineHeight;
	int drawstart;
	int drawend;
	t_tex_info current;
	int secret_door;
}               t_render;

typedef struct  s_texture
{
	t_tex_info north;
	t_tex_info south;
	t_tex_info east;
	t_tex_info west;
	t_tex_info sprite;
	t_tex_info door;
	t_tex_info dead;
	t_tex_info hud;
}               t_texture;

typedef struct  s_data
{
	void *mlx_ptr;
	void *win_ptr;
	char **map;
	t_image *image;
	t_texture *tex;
	t_info  *info;
	t_player *player;
	int secret_key;
	int save;
	t_sprite sprite;
}               t_data;

typedef struct	s_rgba
{
	uint8_t		b;
	uint8_t		g;
	uint8_t		r;
	uint8_t		a;
}				t_rgba;

typedef union	u_color
{
	int			value;
	t_rgba		rgba;
}				t_color;

#endif