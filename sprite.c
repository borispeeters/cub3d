/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 17:26:48 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/24 12:29:51 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	swap_sprites(double **sprites, int i)
{
	double	temp;
	int		j;

	j = 0;
	while (j < 4)
	{
		temp = sprites[i][j];
		sprites[i][j] = sprites[i - 1][j];
		sprites[i - 1][j] = temp;
		j++;
	}
}

static void	sortsprites(double **sprites, t_data *data)
{
	int		i;
	int		sort;

	sort = 0;
	while (!sort)
	{
		sort = 1;
		i = 0;
		while (i + 1 < data->num_sprite)
		{
			i++;
			if (sprites[i][2] > sprites[i - 1][2])
			{
				swap_sprites(sprites, i);
				sort = 0;
			}
		}
	}
}

static void	sprite_dist(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_sprite)
	{
		data->sprites[i][2] = pow(data->posx - data->sprites[i][0], 2) +
		pow(data->posy - data->sprites[i][1], 2);
		i++;
	}
	sortsprites(data->sprites, data);
}

void		sprite_cast(t_data *data, t_ray *ray, int bool)
{
	t_sprite		sprite;

	sprite_dist(data);
	sprite.i = 0;
	while (sprite.i < data->num_sprite)
	{
		if (data->sprites[sprite.i][3] == 0)
		{
			sprite.i++;
			continue ;
		}
		sprite_calc(&sprite, data);
		calc_sprite_draw(&sprite, data);
		draw_sprite(ray, data, &sprite, bool);
		sprite.i++;
	}
}
