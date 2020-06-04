/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 21:02:04 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/26 13:03:24 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	rotate_player(t_data *data, double rotspeed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirx;
	data->dirx = olddirx * cos(rotspeed) - data->diry * sin(rotspeed);
	data->diry = data->diry * cos(rotspeed) + olddirx * sin(rotspeed);
	oldplanex = data->planex;
	data->planex = oldplanex * cos(rotspeed) - data->planey * sin(rotspeed);
	data->planey = oldplanex * sin(rotspeed) + data->planey * cos(rotspeed);
}

void	move_forward(t_data *data, double movespeed, double buf)
{
	if (data->map[(int)data->posy]
	[(int)(data->posx + data->dirx * movespeed * buf)] == 0)
		data->posx += data->dirx * movespeed;
	if (data->map[(int)(data->posy + data->diry * movespeed * buf)]
	[(int)data->posx] == 0)
		data->posy += data->diry * movespeed;
}

void	move_backwards(t_data *data, double movespeed, double buf)
{
	if (data->map[(int)data->posy]
	[(int)(data->posx - data->dirx * movespeed * buf)] == 0)
		data->posx -= data->dirx * movespeed;
	if (data->map[(int)(data->posy - data->diry * movespeed * buf)]
	[(int)data->posx] == 0)
		data->posy -= data->diry * movespeed;
}

void	move_left(t_data *data, double movespeed, double buf)
{
	if (data->map[(int)data->posy]
	[(int)(data->posx + data->diry * movespeed * buf)] == 0)
		data->posx += data->diry * movespeed;
	if (data->map[(int)(data->posy + data->dirx * -movespeed * buf)]
	[(int)data->posx] == 0)
		data->posy += data->dirx * -movespeed;
}

void	move_right(t_data *data, double movespeed, double buf)
{
	if (data->map[(int)data->posy]
	[(int)(data->posx - data->diry * movespeed * buf)] == 0)
		data->posx -= data->diry * movespeed;
	if (data->map[(int)(data->posy - data->dirx * -movespeed * buf)]
	[(int)data->posx] == 0)
		data->posy -= data->dirx * -movespeed;
}
