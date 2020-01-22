/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:54:22 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/21 20:55:16 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		check_info_textures(char *str, t_data *data)
{
	if (ft_strnstr(str, "NO ", 3) || ft_strnstr(str, "SO ", 3) ||
		ft_strnstr(str, "WE ", 3) || ft_strnstr(str, "EA", 3) ||
		ft_strnstr(str, "S ", 2) || ft_strnstr(str, "D ", 2) ||
		ft_strnstr(str, "DEAD ", 5) || ft_strnstr(str, "HUD ", 4))
		return (1);
	return (0);
}

int		check_info(char *str, t_data *data)
{
	if (ft_strnstr(str, "R ", 2) || ft_strnstr(str, "NO ", 3) ||
		ft_strnstr(str, "SO ", 3) || ft_strnstr(str, "WE ", 3) ||
		ft_strnstr(str, "EA", 3) || ft_strnstr(str, "S ", 2) ||
		ft_strnstr(str, "F ", 2) || ft_strnstr(str, "C ", 2) ||
		ft_strnstr(str, "D ", 2) || ft_strnstr(str, "DEAD ", 5) ||
		ft_strnstr(str, "HUD ", 4))
		return (1);
	return (0);
}

int		check_info_c_f(char *str, t_data *data)
{
	if (ft_strnstr(str, "F ", 2) || ft_strnstr(str, "C ", 2))
		return (1);
	return (0);
}
