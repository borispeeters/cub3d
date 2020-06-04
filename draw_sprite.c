/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprite.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 17:29:02 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/28 16:33:36 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <mlx.h>

static void	draw_sprite_verline(t_ray *ray, t_data *data, t_sprite *sprite, \
int bool)
{
	unsigned int	color;
	int				type;

	if (data->map[(int)data->sprites[sprite->i][1]]
	[(int)data->sprites[sprite->i][0]] == 2)
		type = 4;
	else if (data->map[(int)data->sprites[sprite->i][1]]
	[(int)data->sprites[sprite->i][0]] == 3)
		type = 7;
	while (ray->y < sprite->drawendy)
	{
		sprite->d = (ray->y) * 256 - data->screenheight * 128 +
		sprite->spriteheight * 128;
		ray->texy = ((sprite->d * data->tex[type]->img_height) /
		sprite->spriteheight) / 256;
		color = *(unsigned int*)(data->tex[type]->addr +
		(ray->texy * data->tex[type]->size_line +
		ray->texx * (data->tex[type]->bits_per_pixel / 8)));
		color = fog_color(data->sprites[sprite->i][2] / 8, color);
		color = (color & 0X00FFFFFF);
		if (color != 0)
			mlx_pixel_to_image(data->img[bool], sprite->stripe, ray->y, color);
		ray->y++;
	}
}

void		draw_sprite(t_ray *ray, t_data *data, t_sprite *sprite, int bool)
{
	int	type;

	if (data->map[(int)data->sprites[sprite->i][1]]
	[(int)data->sprites[sprite->i][0]] == 2)
		type = 4;
	else if (data->map[(int)data->sprites[sprite->i][1]]
	[(int)data->sprites[sprite->i][0]] == 3)
		type = 7;
	while (sprite->stripe < sprite->drawendx)
	{
		ray->texx = (int)(256 * (sprite->stripe -
		(-sprite->spritewidth / 2 + sprite->spritescreenx)) *
		data->tex[type]->img_width / sprite->spritewidth) / 256;
		if (sprite->transformy > 0 && sprite->stripe > 0 &&
		sprite->stripe < data->screenwidth &&
		sprite->transformy < data->zbuffer[sprite->stripe])
		{
			ray->y = sprite->drawstarty;
			draw_sprite_verline(ray, data, sprite, bool);
		}
		sprite->stripe++;
	}
}

void		calc_sprite_draw(t_sprite *sprite, t_data *data)
{
	sprite->drawstarty = -sprite->spriteheight / 2 + data->screenheight / 2;
	if (sprite->drawstarty < 0)
		sprite->drawstarty = 0;
	sprite->drawendy = sprite->spriteheight / 2 + data->screenheight / 2;
	if (sprite->drawendy >= data->screenheight)
		sprite->drawendy = data->screenheight - 1;
	sprite->spritewidth = (int)fabs(data->screenheight /
	(sprite->transformy));
	sprite->drawstartx = -sprite->spritewidth / 2 + sprite->spritescreenx;
	if (sprite->drawstartx < 0)
		sprite->drawstartx = 0;
	sprite->drawendx = sprite->spritewidth / 2 + sprite->spritescreenx;
	if (sprite->drawendx >= data->screenwidth)
		sprite->drawendx = data->screenwidth - 1;
	sprite->stripe = sprite->drawstartx;
}

void		sprite_calc(t_sprite *sprite, t_data *data)
{
	sprite->spritex = data->sprites[sprite->i][0] - data->posx;
	sprite->spritey = data->sprites[sprite->i][1] - data->posy;
	sprite->invdet = 1.0 /
	(data->planex * data->diry - data->dirx * data->planey);
	sprite->transformx = sprite->invdet *
	(data->diry * sprite->spritex - data->dirx * sprite->spritey);
	sprite->transformy = sprite->invdet *
	(-data->planey * sprite->spritex + data->planex * sprite->spritey);
	sprite->spritescreenx = (int)((data->screenwidth / 2) *
	(1 + sprite->transformx / sprite->transformy));
	sprite->spriteheight = (int)fabs(data->screenheight /
	(sprite->transformy));
}
