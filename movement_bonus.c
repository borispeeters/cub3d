/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 19:06:00 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/22 19:17:27 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	rotate_player(t_data *data, double rotspeed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirx;
	data->dirx = data->dirx * cos(rotspeed) - data->diry * sin(rotspeed);
	data->diry = olddirx * sin(rotspeed) + data->diry * cos(rotspeed);
	oldplanex = data->planex;
	data->planex = data->planex * cos(rotspeed) - data->planey * sin(rotspeed);
	data->planey = oldplanex * sin(rotspeed) + data->planey * cos(rotspeed);
}

void	move_forward(t_data *data, double movespeed, double buf)
{
	if (data->map[(int)data->posy]
	[(int)(data->posx + data->dirx * movespeed * buf)] == 0)
		data->posx += data->dirx * movespeed;
	pickup_obj(data, (int)(data->posx + data->dirx * movespeed * buf),
	(int)data->posy);
	if (data->map[(int)(data->posy + data->diry * movespeed * buf)]
	[(int)data->posx] == 0)
		data->posy += data->diry * movespeed;
	pickup_obj(data, (int)data->posx,
	(int)(data->posy + data->diry * movespeed * buf));
}

void	move_backwards(t_data *data, double movespeed, double buf)
{
	if (data->map[(int)data->posy]
	[(int)(data->posx - data->dirx * movespeed * buf)] == 0)
		data->posx -= data->dirx * movespeed;
	pickup_obj(data, (int)(data->posx - data->dirx * movespeed * buf),
	(int)data->posy);
	if (data->map[(int)(data->posy - data->diry * movespeed * buf)]
	[(int)data->posx] == 0)
		data->posy -= data->diry * movespeed;
	pickup_obj(data, (int)data->posx,
	(int)(data->posy - data->diry * movespeed * buf));
}

void	move_left(t_data *data, double movespeed, double buf)
{
	if (data->map[(int)data->posy]
	[(int)(data->posx + data->diry * movespeed * buf)] == 0)
		data->posx += data->diry * movespeed;
	pickup_obj(data, (int)(data->posx + data->diry * movespeed * buf),
	(int)data->posy);
	if (data->map[(int)(data->posy + data->dirx * -movespeed * buf)]
	[(int)data->posx] == 0)
		data->posy += data->dirx * -movespeed;
	pickup_obj(data, (int)data->posx,
	(int)(data->posy + data->dirx * -movespeed * buf));
}

void	move_right(t_data *data, double movespeed, double buf)
{
	if (data->map[(int)data->posy]
	[(int)(data->posx - data->diry * movespeed * buf)] == 0)
		data->posx -= data->diry * movespeed;
	pickup_obj(data, (int)(data->posx - data->diry * movespeed * buf),
	(int)data->posy);
	if (data->map[(int)(data->posy - data->dirx * -movespeed * buf)]
	[(int)data->posx] == 0)
		data->posy -= data->dirx * -movespeed;
	pickup_obj(data, (int)data->posx,
	(int)(data->posy - data->dirx * -movespeed * buf));
}
