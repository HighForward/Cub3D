/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 23:20:53 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/22 00:21:51 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_color		c(int v)
{
	t_color c;

	c.value = v;
	return (c);
}

int			convertrgb(int r, int g, int b)
{
	r = (r > 255 ? 255 : r);
	g = (g > 255 ? 255 : g);
	b = (b > 255 ? 255 : b);
	r = (r < 0 ? 0 : r);
	g = (g < 0 ? 0 : g);
	b = (b < 0 ? 0 : b);
	return (65536 * r + 256 * g + b);
}

int			get_darkness(int color, int percent)
{
	t_color current;
	t_color darkness;
	int		coeff;

	percent += 15;
	coeff = percent > 100 ? 100 : percent;
	current.value = color;
	darkness.rgba.r = (current.rgba.r * coeff / 100);
	darkness.rgba.g = (current.rgba.g * coeff / 100);
	darkness.rgba.b = (current.rgba.b * coeff / 100);
	return (darkness.value);
}

int			get_transparency(t_data *data, int source, int destination)
{
	float one;
	float two;
	float result;

	one = (127 * source) / 255;
	two = ((255 - 127) * destination) / 255;
	result = one + two;
	return (result);
}

int			degrade_couleur(int color, int x)
{
	t_color	shade;
	int		j;

	shade.value = color;
	shade.rgba.b += x;
	return (shade.value);
}
