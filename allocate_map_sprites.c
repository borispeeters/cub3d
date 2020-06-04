/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_map_sprites.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 17:39:31 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:14:12 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	allocate_map_height(t_data *data)
{
	data->map = (int**)malloc(sizeof(int*) * (data->mapheight));
	data->mapwidth = (int*)malloc(sizeof(int) * (data->mapheight));
	if (!data->map || !data->mapwidth)
		error_exit("Failed to allocate memory for the map", data);
}

void	allocate_sprites(t_data *data)
{
	data->sprites = (double**)malloc(sizeof(double*) * (data->num_sprite));
	if (!data->sprites)
		error_exit("Failed to allocate memory for the sprites", data);
}
