/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 10:52:02 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/28 16:41:12 by bpeeters      ########   odam.nl         */
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

void		ft_raycast(t_data *data)
{
	t_ray		ray;
	static int	bool;

	draw_fc_tex(data, bool);
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
	draw_health(data, bool);
	if (data->win)
		mlx_put_image_to_window(data->mlx, data->win,
		data->img[bool]->img, 0, 0);
	bool = (bool == 0) ? 1 : 0;
}
