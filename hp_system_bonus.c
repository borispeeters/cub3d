/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hp_system_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 19:07:54 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/24 11:51:50 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_sprite(t_data *data, int x, int y)
{
	data->map[y][x] = 0;
	data->sprites[data->num_sprite - 1][3] = 0;
}

void	pickup_obj(t_data *data, int x, int y)
{
	if (data->map[y][x] == 2)
	{
		remove_sprite(data, x, y);
		gain_health(data);
	}
	if (data->map[y][x] == 3)
		lose_health(data);
}
