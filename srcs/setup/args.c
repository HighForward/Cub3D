/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:44:21 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/21 20:44:21 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		handle_args(t_data *data, char **argv, int argc)
{
	if (argc < 2 || argc > 3)
		return (return_string(0, "Error\n"));
	if (argc == 3 && ft_strnstr(argv[2], "-save", 5))
		data->save = 1;
	else if (argc == 3)
		return (return_string(0, "Error\nUndefined parameter\n"));
	return (1);
}

int		open_file_description(t_data *data, int *fd, char *str)
{
	if (!(wrong_extention(str)))
		return (return_error(0, data, "Error\nWrong map extention\n"));
	if (!((*fd) = open(str, O_RDONLY)))
		return (return_error(0, data, "Error\n"));
	return (1);
}

int		wrong_extention(char *str)
{
	int len;

	if ((len = ft_strlen(str)) <= 4)
		return (0);
	if (ft_strnstr(str + len - 4, ".cub", 4))
		return (1);
	return (0);
}
