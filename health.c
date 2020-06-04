/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   health.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 14:27:42 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/28 16:38:14 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <mlx.h>

void				lose_health(t_data *data)
{
	data->hp -= 0.005;
	if (data->hp < 0)
	{
		game_over(data);
		exit(0);
	}
}

void				gain_health(t_data *data)
{
	data->hp += 0.1;
	if (data->hp > 1.0)
		data->hp = 1.0;
}

static unsigned int	health_color(t_data *data)
{
	t_color pack;

	pack.argb.r = 255;
	pack.argb.r *= (1.0 - data->hp);
	pack.argb.g = 255;
	pack.argb.g *= data->hp;
	pack.argb.b = 0;
	return (pack.color & 0x00FFFFFF);
}

void				draw_health(t_data *data, int bool)
{
	int				x;
	int				y;
	unsigned int	color;

	color = health_color(data);
	x = data->screenwidth * 0.25;
	while (x < data->screenwidth * (0.25 + data->hp * 0.5))
	{
		y = data->screenheight * 0.9;
		while (y < data->screenheight * 0.95)
		{
			mlx_pixel_to_image(data->img[bool], x, y, color);
			y++;
		}
		x++;
	}
}
