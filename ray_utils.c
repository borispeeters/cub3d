/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 19:06:01 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/25 18:14:37 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			mlx_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * img->size_line + x * (img->bits_per_pixel / 8);
	dst = img->addr + offset;
	*(unsigned int*)dst = color;
}

unsigned int	fog_color(double distance, unsigned int color)
{
	t_color pack;
	double	multi;

	multi = (10 / distance) / 3;
	if (multi > 1.0)
		multi = 1.0;
	if (multi < 0.35)
		multi = 0.35;
	pack.argb.r = (color & 0xFF0000) >> 16;
	pack.argb.r *= multi;
	pack.argb.g = (color & 0xFF00) >> 8;
	pack.argb.g *= multi;
	pack.argb.b = color & 0xFF;
	pack.argb.b *= multi;
	return (pack.color & 0x00FFFFFF);
}
