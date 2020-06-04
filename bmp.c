/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 09:01:28 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:45:38 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <mlx.h>
#include "libft.h"

void	render_screenshot(t_data *data, t_img *img)
{
	t_img	texture[8];

	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit("Failed to link software with the display", data);
	data->zbuffer = (double*)malloc(sizeof(double) * data->screenwidth);
	if (!data->zbuffer)
		error_exit("Failed to allocate memory", data);
	data->hp = 1.0;
	create_frames(data, img);
	set_tex_img(data, texture);
	ft_raycast(data);
}

void	set_byte_bmp(unsigned char *bmp, int dec)
{
	int	xand;
	int	shift;
	int	i;

	xand = 255;
	shift = 0;
	i = 0;
	while (i < 4)
	{
		bmp[i] = (dec & xand) >> shift;
		shift += 8;
		xand = xand << 8;
		i++;
	}
}

void	draw_screenshot(t_data *data, t_bitmap *bmp)
{
	t_color	pack;
	int		x;
	int		y;

	ft_memset(bmp->pad, (unsigned char)0, 3);
	y = data->screenheight;
	while (y > 0)
	{
		y--;
		x = 0;
		while (x < data->screenwidth)
		{
			pack.color = *(unsigned int*)(data->img[0]->addr +
			(y * data->img[0]->size_line +
			x * (data->img[0]->bits_per_pixel / 8)));
			bmp->px[0] = pack.argb.b;
			bmp->px[1] = pack.argb.g;
			bmp->px[2] = pack.argb.r;
			if (write(bmp->fd, bmp->px, 3) == -1)
				error_exit("Write failed", data);
			x++;
		}
		if (write(bmp->fd, bmp->pad, bmp->padding) == -1)
			error_exit("Write failed", data);
	}
}

void	draw_bmp_header(t_data *data, t_bitmap *bmp)
{
	ft_memset(bmp->header, (unsigned char)0, 54);
	set_byte_bmp(bmp->header, (77 << 8) + 66);
	set_byte_bmp(bmp->header + 2, bmp->filesize);
	set_byte_bmp(bmp->header + 10, 54);
	set_byte_bmp(bmp->header + 14, 40);
	set_byte_bmp(bmp->header + 18, data->screenwidth);
	set_byte_bmp(bmp->header + 22, data->screenheight);
	set_byte_bmp(bmp->header + 26, 1);
	set_byte_bmp(bmp->header + 28, 24);
	if (write(bmp->fd, bmp->header, 54) == -1)
		error_exit("Write failed", data);
}

void	write_bmp(t_data *data)
{
	t_bitmap	bmp;
	t_img		img[2];

	render_screenshot(data, img);
	bmp.padding = (4 - ((data->screenwidth * 3) % 4)) % 4;
	bmp.filesize = 54 + 3 *
	((data->screenwidth + bmp.padding) * data->screenheight);
	bmp.fd = open("screenshot.bmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (bmp.fd == -1)
		error_exit("Failed to create .bmp file", data);
	draw_bmp_header(data, &bmp);
	draw_screenshot(data, &bmp);
	if (close(bmp.fd) == -1)
		error_exit("Failed to close .bmp file", data);
}
