/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:57:47 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/21 23:56:11 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_vector		vec(float x, float y)
{
	t_vector ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

t_spawn_player	vec_s(int x, int y)
{
	t_spawn_player ret;

	ret.spawn_x = x;
	ret.spawn_y = y;
	return (ret);
}

t_index			vec_i(int x, int y)
{
	t_index ret;

	ret.i = x;
	ret.j = y;
	return (ret);
}

int				size_map(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
