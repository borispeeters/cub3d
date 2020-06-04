/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   events.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 21:04:31 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:08:51 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdlib.h>

int		quit_program(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img[0]->img);
	mlx_destroy_image(data->mlx, data->img[1]->img);
	exit(0);
}

int		mouse_movement(int x, int y, t_data *data)
{
	double	rotspeed;

	rotspeed = 0.04;
	data->key_rot_left = 0;
	data->key_rot_right = 0;
	if (y < 0 || y >= data->screenheight || x < 0 || x >= data->screenwidth)
		return (1);
	if (x < data->screenwidth / 3)
		data->key_rot_left = 1;
	if (x > (data->screenwidth / 3) * 2)
		data->key_rot_right = 1;
	return (0);
}

int		key_check(t_data *data)
{
	double	movespeed;
	double	rotspeed;
	double	buf;

	movespeed = 0.08;
	rotspeed = 0.04;
	buf = 2.0;
	if (data->key_forward == 1)
		move_forward(data, movespeed, buf);
	if (data->key_back == 1)
		move_backwards(data, movespeed, buf);
	if (data->key_left == 1)
		move_left(data, movespeed, buf);
	if (data->key_right == 1)
		move_right(data, movespeed, buf);
	if (data->key_rot_right == 1)
		rotate_player(data, rotspeed);
	if (data->key_rot_left == 1)
		rotate_player(data, -rotspeed);
	if (data->key_forward == 1 || data->key_back == 1 ||
	data->key_left == 1 || data->key_right == 1 ||
	data->key_rot_left == 1 || data->key_rot_right == 1)
		ft_raycast(data);
	return (0);
}

int		key_release(int keycode, t_data *data)
{
	if (keycode == 13)
		data->key_forward = 0;
	if (keycode == 1)
		data->key_back = 0;
	if (keycode == 2)
		data->key_right = 0;
	if (keycode == 0)
		data->key_left = 0;
	if (keycode == 124)
		data->key_rot_right = 0;
	if (keycode == 123)
		data->key_rot_left = 0;
	return (0);
}

int		key_press(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img[0]->img);
		mlx_destroy_image(data->mlx, data->img[1]->img);
		exit(0);
	}
	if (keycode == 13)
		data->key_forward = 1;
	if (keycode == 1)
		data->key_back = 1;
	if (keycode == 2)
		data->key_right = 1;
	if (keycode == 0)
		data->key_left = 1;
	if (keycode == 124)
		data->key_rot_right = 1;
	if (keycode == 123)
		data->key_rot_left = 1;
	return (0);
}
