/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_pos.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 18:27:13 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:23:23 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	set_north(t_data *data, int i, int k)
{
	if (data->start)
		error_exit("Start pos and dir given twice in map", data);
	data->start = 1;
	data->posx = k + 0.5;
	data->posy = i + 0.5;
	data->dirx = 0;
	data->diry = -1;
	data->planex = 0.66;
	data->planey = 0;
}

void	set_south(t_data *data, int i, int k)
{
	if (data->start)
		error_exit("Start pos and dir given twice in map", data);
	data->start = 1;
	data->posx = k + 0.5;
	data->posy = i + 0.5;
	data->dirx = 0;
	data->diry = 1;
	data->planex = -0.66;
	data->planey = 0;
}

void	set_east(t_data *data, int i, int k)
{
	if (data->start)
		error_exit("Start pos and dir given twice in map", data);
	data->start = 1;
	data->posx = k + 0.5;
	data->posy = i + 0.5;
	data->dirx = 1;
	data->diry = 0;
	data->planex = 0;
	data->planey = 0.66;
}

void	set_west(t_data *data, int i, int k)
{
	if (data->start)
		error_exit("Start pos and dir given twice in map", data);
	data->start = 1;
	data->posx = k + 0.5;
	data->posy = i + 0.5;
	data->dirx = -1;
	data->diry = 0;
	data->planex = 0;
	data->planey = -0.66;
}

void	set_sprite(t_data *data, int i, int k, int obj)
{
	data->map[i][k] = obj;
	data->sprites[data->num_sprite] = (double*)malloc(sizeof(double) * (4));
	if (!data->sprites[data->num_sprite])
		error_exit("Failed to allocate memory for a sprite", data);
	data->sprites[data->num_sprite][0] = k + 0.5;
	data->sprites[data->num_sprite][1] = i + 0.5;
	data->sprites[data->num_sprite][3] = obj;
	data->num_sprite++;
}
