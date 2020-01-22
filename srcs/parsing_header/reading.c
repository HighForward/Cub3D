/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:51:08 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/21 20:51:08 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		parse_map(t_data *data, char *s, int *i)
{
	if (check_info(s, data))
	{
		if (ft_strnstr(s, "R ", 2) && data->info->height == 0 &&
			data->info->width == 0)
		{
			if (parse_map_info_window(s, &data->info->height,
				&data->info->width, 1 + skip_space(s + 1)) == 0)
				return (return_string(-1, "Error\nWrong resolution\n"));
		}
		else if (check_info_textures(s, data))
			parse_info_textures(s, data);
		else if (check_info_c_f(s, data))
		{
			if (parse_info_c_f(s, data) == -1)
				return (return_string(-1, "Error\nWrong colors RGB\n"));
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

int		info_header_cub(int fd, t_data *data)
{
	int		i;
	int		ret;
	char	*line;

	i = 0;
	while (i != 11)
	{
		if ((ret = get_next_line(fd, &line)) <= 0)
		{
			if (ret == -1)
				return (return_string(0, "Error\nEmpty map\n"));
			else
				return (free_and_return(1, line));
		}
		if (parse_map(data, line, &i) == -1)
			return (free_and_return(0, line));
		free(line);
	}
	return (1);
}
