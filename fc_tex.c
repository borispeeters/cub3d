/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fc_tex.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 17:31:09 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/28 16:34:30 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

static void	put_fc_img(t_ray *ray, t_data *data, int bool, int type)
{
	unsigned int	color;

	ray->tx = (int)(data->tex[type]->img_width * (ray->floorx - ray->cellx))
	& (data->tex[type]->img_width - 1);
	ray->ty = (int)(data->tex[type]->img_height * (ray->floory - ray->celly))
	& (data->tex[type]->img_height - 1);
	color = *(unsigned int*)(data->tex[type]->addr +
	(ray->ty * data->tex[type]->size_line + ray->tx *
	(data->tex[type]->bits_per_pixel / 8)));
	color = fog_color((double)ray->rowdistance, color);
	mlx_pixel_to_image(data->img[bool], ray->x, ray->y, color);
}

static void	calculate_fc_tex(t_ray *ray, t_data *data)
{
	ray->raydirx0 = data->dirx - data->planex;
	ray->raydiry0 = data->diry - data->planey;
	ray->raydirx1 = data->dirx + data->planex;
	ray->raydiry1 = data->diry + data->planey;
	ray->rowdistance = (data->screenheight / 2.0) /
	(ray->y - data->screenheight / 2);
	ray->floorstepx = ray->rowdistance *
	(ray->raydirx1 - ray->raydirx0) / data->screenwidth;
	ray->floorstepy = ray->rowdistance *
	(ray->raydiry1 - ray->raydiry0) / data->screenwidth;
	ray->floorx = data->posx + ray->rowdistance * ray->raydirx0;
	ray->floory = data->posy + ray->rowdistance * ray->raydiry0;
}

void		draw_fc_tex(t_data *data, int bool)
{
	t_ray	ray;
	int		tmp_y;

	ray.y = 0;
	while (ray.y < data->screenheight)
	{
		calculate_fc_tex(&ray, data);
		ray.x = 0;
		while (ray.x < data->screenwidth)
		{
			ray.cellx = (int)ray.floorx;
			ray.celly = (int)ray.floory;
			ray.floorx += ray.floorstepx;
			ray.floory += ray.floorstepy;
			put_fc_img(&ray, data, bool, 5);
			tmp_y = ray.y;
			ray.y = data->screenheight - ray.y - 1;
			put_fc_img(&ray, data, bool, 6);
			ray.y = tmp_y;
			ray.x++;
		}
		ray.y++;
	}
}
