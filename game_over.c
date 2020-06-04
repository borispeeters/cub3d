/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_over.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 17:26:19 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 14:20:23 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdlib.h>

static int	end_game(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img[0]->img);
		mlx_destroy_image(data->mlx, data->img[1]->img);
		exit(0);
	}
	return (0);
}

static void	red_screen(t_data *data)
{
	int				x;
	int				y;

	x = 0;
	while (x < data->screenwidth)
	{
		y = 0;
		while (y < data->screenheight)
		{
			mlx_pixel_to_image(data->img[0], x, y, 0xFF0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img[0]->img, 0, 0);
}

void		game_over(t_data *data)
{
	red_screen(data);
	mlx_string_put(data->mlx, data->win, data->screenwidth * 0.45,
	data->screenheight * 0.45, 0xFFFFFF, "YOU HAVE DIED");
	mlx_string_put(data->mlx, data->win, data->screenwidth * 0.45,
	data->screenheight * 0.55, 0xFFFFFF, "leave: [esc]");
	mlx_hook(data->win, 2, 1L << 0, end_game, data);
	mlx_loop(data->mlx);
}
