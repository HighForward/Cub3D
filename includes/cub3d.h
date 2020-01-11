#ifndef CUB3D_H
# define CUB3D_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"
#include "structures.h"
#include <math.h>

#define STEP 0.25f
#define VIEW 2.5f

int     free_and_return(int value, char *str);
int     return_error(int value, t_data *data, char *str);
int		return_string(int value, char *str);
int		return_string_free(int value, char *str);
int     close_red_button(t_data *game);
void	initialize_struct_texture(t_data *data);

int     open_file_description(t_data *data, int *fd, char *str);

// PARSING INFOS CUB
int		skip_space(char *str);
int     info_header_cub(int fd, t_data *data);
int     parse_map(t_data *data, char *s, int *i);
int     check_info(char *str, t_data *data);
int     parse_map_info_window(char *str, int *dest1, int *dest2, int start);
int     fill_textures(t_data *data, t_tex_info *info);
int     get_texture_C_F(char *str, int i, int *color);

// CREATE IMG AND LOAD TEXTURES
int     create_image(t_data *data);
int     load_texture(t_data *data);

// GET MAP
void	cut_space(char **line);
int		free_entire_map(char **str);
int     check_map(int fd, t_data *data);
int		fill_map(t_data *data, char *line, int *secure);
int		fill_temp_map(t_data *data, char *line, char **temp);
int     fill_last_line(t_data *data, char *line, int *secure);
int     fill_full_map(t_data *data);

// PARSING MAP
int     is_valid_line(char *s);
int     get_position(t_data *data);
void    get_orientation(t_data *data, float x, float y, float cam_x, float cam_y);
int     map_is_not_close(t_data *data);

// EVENT
int     get_event(int key, t_data *data);
void    rotate_player(t_player *player, float angle);
void    move_front_back(t_data *data, float move);
void    move_side(t_data *data, float move);
void    direction(t_vector *v, float angle);
void    obstacle(t_data *data, float move);

// MINIMAP
void    print_map(t_data *data);
void    ft_putpixel(char *line, int i, t_data *data);
void    display_rekt(int x, int y, int color, t_data *data);
int     print_render(t_data *data);

// HUD
int		display(t_data *data);
int		display_cross(t_data *data);
int     display_cross_circle(int x, int y, t_data *data, int color);
int		display_cross_pixel(int x, int y, t_data *data, int color);
int		display_cross_around(t_data *data, int color);
int     display_lifebar(t_data *data);
void    take_damage(t_data *data, int value);
void    get_view_vertical(int key, t_data *data);

// COLOR
int     get_transparency(t_data *data, int color, int destination);
int     convertRGB(int R, int G, int B);
t_color    c(int v);

// SECRETDOOR
void    handle_secret_door(t_data *data, t_render *render, t_ray ray);
void    leave_secret_door(t_data *data);

// RENDER

int		get_wall(t_data *data, t_ray ray);
void    get_wall_dda(t_data *data, t_render *render, t_ray ray);
void    setup_ray_render(t_data *data, t_render *render, t_ray);
void    load_line_buffer(t_data *data, t_render render, t_ray ray, t_line size, t_tex_info current, int **buffer);
void    print_lines(t_data *data, t_line line, t_ray ray, int *buffer);
int		display_view(t_player *p, t_data *data);
int		display_line(t_data *data, float step, int i);
int		get_size_line(t_data *data, t_ray ray, t_render render);


t_tex_info		current_texture(t_data *data, t_render render);

#endif