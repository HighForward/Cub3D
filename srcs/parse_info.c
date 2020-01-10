#include "../includes/cub3d.h"

int		skip_space(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int     check_info(char *str, t_data *data)
{
    if (ft_strnstr(str, "R ", 2) || ft_strnstr(str, "NO ", 3) || ft_strnstr(str, "SO ", 3) ||
        ft_strnstr(str, "WE ", 3) || ft_strnstr(str, "EA", 3) || ft_strnstr(str, "S ", 2) ||
        ft_strnstr(str, "F ", 2) || ft_strnstr(str, "C ", 2) || ft_strnstr(str, "D ", 2))
        return (1);
    return (0);
}

int     get_value_window(char *s, int *i)
{
    int nb;
    int x;

    x = 0;
    nb = 0;
    if ((s[x] >= '0' && s[x] <= '9'))
    {
        while ((s[x] && (s[x] >= '0' && s[x] <= '9')))
        {
            nb = nb * 10 + (s[x] - 48);
            (x)++;
        }
        (*i) += x;
        return (nb);
    }
    return (0);
}

int     parse_map_info_window(char *str, int *dest1, int *dest2, int start)
{
    char *temp;
    int i;

    *dest1 = 0;
    *dest2 = 0;
    i = 0;
    temp = &str[start];
    if (temp[i] >= '0' && temp[i] <= '9')
        *dest2 = get_value_window(&temp[i], &i);
    else
        return (0);
    if (temp[i] == ' ')
        i++;
    else
        return (0);
    if (temp[i] >= '0' && temp[i] <= '9')
        *dest1 = get_value_window(&temp[i], &i);
    else
        return (0);
    if (ft_isprint(temp[i]))
    	return (0);
    *dest2 = *dest2 < 500 ? 500 : *dest2;
    *dest1 = *dest1 < 500 ? 500 : *dest1;
    *dest2 = *dest2 < *dest1 ? *dest1 : *dest2;

    return (1);
}

int     get_texture_C_F(char *str, int i, int *color)
{
	t_color temp_color;

    if (str[i] >= '0' && str[i] <= '9')
    {
        temp_color.rgba.r = get_value_window(&str[i], &i);
        if (str[i++] == ',')
        {
            if (str[i] >= '0' && str[i] <= '9')
            {
            	temp_color.rgba.g = get_value_window(&str[i], &i);
                if (str[i++] == ',')
                {
                    if (str[i] >= '0' && str[i] <= '9')
                    {
                        temp_color.rgba.b = get_value_window(&str[i], &i);
                        (*color) = temp_color.value;
                        if (ft_isprint(str[i]))
                        	return (0);
                        return (1);
                    }
                }
            }
        }
    }
    return (0);
}

int     parse_map(t_data *data, char *s, int *i)
{
    if (check_info(s, data))
    {
        if (ft_strnstr(s, "R ", 2))
        {
            if (parse_map_info_window(s, &data->info->height, &data->info->width, 1 + skip_space(s + 1)) == 0)
                return (return_string(-1, "Error\nWrong resolution\n"));
        }
        else if (ft_strnstr(s, "NO ", 3) && data->tex->north.path == NULL)
			data->tex->north.path = ft_strdup(s + 2 + skip_space(s + 2));
        else if (ft_strnstr(s, "SO ", 3) && data->tex->south.path == NULL)
			data->tex->south.path = ft_strdup(s + 2 + skip_space(s + 2));
        else if (ft_strnstr(s, "WE ", 3) && data->tex->west.path == NULL)
			data->tex->west.path = ft_strdup(s + 2 + skip_space(s + 2));
        else if (ft_strnstr(s, "EA ", 3) && data->tex->east.path == NULL)
			data->tex->east.path = ft_strdup(s + 2 + skip_space(s + 2));
        else if (ft_strnstr(s, "S ", 2) && data->tex->sprite.path == NULL)
			data->tex->sprite.path = ft_strdup(s + 1 + skip_space(s + 1));
        else if (ft_strnstr(s, "D ", 2) && data->tex->door.path == NULL)
			data->tex->door.path = ft_strdup(s + 1 + skip_space(s + 1));
        else if (ft_strnstr(s, "F ", 2))
        {
            if (get_texture_C_F(s, 1 + skip_space(s + 1), &data->info->color_floor) == 0)
                return (0);
        }
        else if (ft_strnstr(s, "C ", 2))
        {
            if (get_texture_C_F(s, 1 + skip_space(s + 1), &data->info->color_cellar) == 0)
                return (0);
        }
        else
			return (return_string(-1, "Error\nDouble path detected\n"));
        (*i)++;
        return (1);
    }
    else if (ft_strlen(s) > 0)
        return (return_string(-1, "Error\nWrong line in Header\n"));
    return (0);
}

int     info_header_cub(int fd, t_data *data)
{
    int i;
    int ret;
    char *line;

    i = 0;
    while (i != 9)
    {
        if ((ret = get_next_line(fd, &line)) <= 0)
		{
        	if (ret == -1)
        		return (return_string(0, "Error\nEmpty map\n"));
        	else
				return (free_and_return(0, line));
		}
        if (parse_map(data, line, &i) == -1)
            return (free_and_return(0, line));
        free(line);
    }
    return (1);
}