/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycalc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 17:11:14 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/22 10:51:03 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	calc_ray(t_ray *ray, t_data *data)
{
	ray->camerax = 2 * ray->x / ((double)data->screenwidth - 1) - 1;
	ray->raydirx = data->dirx + data->planex * ray->camerax;
	ray->raydiry = data->diry + data->planey * ray->camerax;
	ray->deltadistx = fabs(1 / ray->raydirx);
	ray->deltadisty = fabs(1 / ray->raydiry);
	ray->mapx = (int)data->posx;
	ray->mapy = (int)data->posy;
}

void	calc_raydist(t_ray *ray, t_data *data)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (data->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - data->posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (data->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - data->posy) * ray->deltadisty;
	}
}

void	ft_dda(t_ray *ray, t_data *data)
{
	while (1)
	{
		if (ray->sidedisty < ray->sidedistx)
		{
			if (ray->stepy < 0)
				ray->side = 0;
			else
				ray->side = 1;
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
		}
		else if (ray->sidedistx < ray->sidedisty)
		{
			if (ray->stepx < 0)
				ray->side = 3;
			else
				ray->side = 2;
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
		}
		if (data->map[ray->mapy][ray->mapx] == 1)
			break ;
	}
}

void	calc_verline(t_ray *ray, t_data *data)
{
	if (ray->side == 0 || ray->side == 1)
		ray->perpwalldist = (ray->mapy - data->posy +
		(1 - ray->stepy) / 2) / ray->raydiry;
	else if (ray->side == 2 || ray->side == 3)
		ray->perpwalldist = (ray->mapx - data->posx +
		(1 - ray->stepx) / 2) / ray->raydirx;
	ray->lineheight = (int)(data->screenheight / ray->perpwalldist);
}

void	calc_drawpos(t_ray *ray, t_data *data)
{
	calc_verline(ray, data);
	ray->drawstart = data->screenheight / 2 - ray->lineheight / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = data->screenheight / 2 + ray->lineheight / 2;
	if (ray->drawend >= data->screenheight)
		ray->drawend = data->screenheight - 1;
	if (ray->side == 0 || ray->side == 1)
		ray->wallx = data->posx + ray->perpwalldist * ray->raydirx;
	else if (ray->side == 2 || ray->side == 3)
		ray->wallx = data->posy + ray->perpwalldist * ray->raydiry;
	ray->wallx -= floor(ray->wallx);
	ray->texx = (int)(ray->wallx * (double)data->tex[ray->side]->img_width);
	if ((ray->side == 0 || ray->side == 1) && ray->raydiry < 0)
		ray->texx = data->tex[ray->side]->img_width - ray->texx - 1;
	else if ((ray->side == 2 || ray->side == 3) && ray->raydirx > 0)
		ray->texx = data->tex[ray->side]->img_width - ray->texx - 1;
	ray->step = 1.0 * data->tex[ray->side]->img_height / ray->lineheight;
	ray->texpos = (ray->drawstart - data->screenheight / 2 +
	ray->lineheight / 2) * ray->step;
	ray->y = ray->drawstart;
}
