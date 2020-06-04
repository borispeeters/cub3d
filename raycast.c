/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 17:13:23 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/28 16:41:42 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

static void	draw_verline(t_ray *ray, t_data *data, int bool)
{
	unsigned int	color;

	while (ray->y <= ray->drawend)
	{
		ray->texy = (int)ray->texpos & (data->tex[ray->side]->img_height - 1);
		ray->texpos += ray->step;
		color = *(unsigned int*)(data->tex[ray->side]->addr +
		(ray->texy * data->tex[ray->side]->size_line +
		ray->texx * (data->tex[ray->side]->bits_per_pixel / 8)));
		color = fog_color(ray->perpwalldist, color);
		mlx_pixel_to_image(data->img[bool], ray->x, ray->y, color);
		ray->y++;
	}
}

static void	draw_fc(t_data *data, int bool)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->screenwidth)
	{
		y = 0;
		while (y < data->screenheight / 2)
		{
			mlx_pixel_to_image(data->img[bool], x, y, data->ceiling);
			y++;
		}
		while (y < data->screenheight)
		{
			mlx_pixel_to_image(data->img[bool], x, y, data->floor);
			y++;
		}
		x++;
	}
}

void		ft_raycast(t_data *data)
{
	t_ray		ray;
	static int	bool;

	draw_fc(data, bool);
	ray.x = 0;
	while (ray.x < data->screenwidth)
	{
		calc_ray(&ray, data);
		calc_raydist(&ray, data);
		ft_dda(&ray, data);
		calc_drawpos(&ray, data);
		draw_verline(&ray, data, bool);
		data->zbuffer[ray.x] = ray.perpwalldist;
		ray.x++;
	}
	sprite_cast(data, &ray, bool);
	if (data->win)
		mlx_put_image_to_window(data->mlx, data->win,
		data->img[bool]->img, 0, 0);
	bool = (bool == 0) ? 1 : 0;
}
