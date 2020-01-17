/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 08:33:36 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/10 15:55:45 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void cut_space(char **line)
{
	int i;
	int space;
	char *dup;

	space = 0;
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] != ' ')
			space++;
		i++;
	}
	dup = ft_strnew(space);
	space = 0;
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] != ' ')
		{
			dup[space] = (*line)[i];
			space++;
		}
		i++;
	}
	dup[space] = '\0';
	free((*line));
	(*line) = dup;
}

int free_entire_map(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_bzero(str[i], ft_strlen(str[i]));
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
	return (1);
}

int fill_temp_map(t_data *data, char *line, char **temp)
{
	(*temp) = ft_strnew(ft_strlen(data->map[0]) + ft_strlen(line) + 1);
	(*temp) = ft_strncat((*temp), data->map[0], ft_strlen(data->map[0]));
	(*temp) = ft_strncat((*temp), "\n", 1);
	(*temp) = ft_strncat((*temp), line, ft_strlen(line));
	free_entire_map(data->map);
	data->map = malloc(sizeof(char *) * 2);
	data->map[0] = ft_strdup((*temp));
	data->map[1] = NULL;
	free((*temp));
	free(line);
	return (1);
}

int fill_map(t_data *data, char *line, int *secure)
{
	int i;
	char *temp;

	i = 0;
	if (data->map == NULL)
	{
		data->map = malloc(sizeof(char *) * 2);
		data->map[0] = ft_strdup(line);
		data->map[1] = NULL;
		free(line);
		return (1);
	}
	fill_temp_map(data, line, &temp);
	(*secure)++;
	return (1);
}

int fill_full_map(t_data *data)
{
	char *temp;

	temp = ft_strnew(ft_strlen(data->map[0]));
	temp = ft_strcpy(temp, data->map[0]);
	free_entire_map(data->map);
	data->map = ft_split(temp, '\n');
	free(temp);
	return (1);
}

int fill_last_line(t_data *data, char *line, int *secure)
{
	if (line[0] == '1')
	{
		if (!is_valid_line(line))
			return (return_string(0, "Error\nUndetermined object found\n"));
		fill_map(data, line, secure);
	} else if (ft_strlen(line) > 0)
		return (free_and_return(return_string(0, "Error\nNo empty line\n"), line));
	else
		free(line);
	return (1);
}

int check_map(int fd, t_data *data)
{
	char *line;
	int secure;

	secure = 0;
	while (get_next_line(fd, &line))
	{
		if (line[0] == '1')
		{
			cut_space(&line);
			if (!is_valid_line(line))
				return (return_string(0, "Error\nUndetermined object found\n"));
			fill_map(data, line, &secure);
		} else if (!ft_strlen(line) && secure)
			return (free_and_return(return_string(0, "Error\nEmpty line found\n"), line));
		else
		{
			if (ft_strlen(line) > 0)
				return (free_and_return(return_string(0, "Error\nWrong line found\n"), line));
			free(line);
		}
	}
	if (fill_last_line(data, line, &secure) == 0)
		return (0);
	if (data->map == NULL)
		return (0);
	if (fill_full_map(data) == 0)
		return (0);
	if ((get_position(data)) == 0)
		return (0);
	if ((map_is_not_close(data)) == 0)
		return (0);
	return (1);
}
