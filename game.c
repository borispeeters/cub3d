/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 17:20:36 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:18:01 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include "libft.h"

static void	check_filetype(char *str, t_data *data, int i)
{
	int	offset;

	offset = ft_strlen(str) - 4;
	if (offset < 0)
		error_exit("Image is not in png or xpm format", data);
	if (ft_strncmp(str + offset, ".png", 3) == 0)
		data->tex[i]->img = mlx_png_file_to_image(data->mlx, data->path[i],
		&data->tex[i]->img_width, &data->tex[i]->img_height);
	else if (ft_strncmp(str + offset, ".xpm", 3) == 0)
		data->tex[i]->img = mlx_xpm_file_to_image(data->mlx, data->path[i],
		&data->tex[i]->img_width, &data->tex[i]->img_height);
	else
		error_exit("File is not of png or xpm type", data);
	if (!data->tex[i]->img)
		error_exit("Failed to create image", data);
}

void		set_tex_img(t_data *data, t_img *texture)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data->tex[i] = &texture[i];
		check_filetype(data->path[i], data, i);
		data->tex[i]->addr = mlx_get_data_addr(data->tex[i]->img,
		&data->tex[i]->bits_per_pixel, &data->tex[i]->size_line,
		&data->tex[i]->endian);
		i++;
	}
}

void		create_frames(t_data *data, t_img *img)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		data->img[i] = &img[i];
		data->img[i]->img = mlx_new_image(data->mlx,
		data->screenwidth, data->screenheight);
		if (!data->img[i]->img)
			error_exit("Failed to create new image", data);
		data->img[i]->addr = mlx_get_data_addr(data->img[i]->img,
		&data->img[i]->bits_per_pixel, &data->img[i]->size_line,
		&data->img[i]->endian);
		i++;
	}
}

static void	ft_mlx_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_movement, data);
	mlx_hook(data->win, 17, 1L << 17, quit_program, data);
	mlx_loop_hook(data->mlx, key_check, data);
	mlx_loop(data->mlx);
}

void		init_mlx(t_data *data)
{
	t_img	texture[5];
	t_img	img[2];
	char	title[12];

	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit("Failed to link software with the display", data);
	cat_title_res(data, title);
	data->win = mlx_new_window(data->mlx, data->screenwidth,
	data->screenheight, title);
	if (!data->win)
		error_exit("Failed to create window", data);
	data->zbuffer = (double*)malloc(sizeof(double) * data->screenwidth);
	if (!data->zbuffer)
		error_exit("Failed to allocate memory", data);
	create_frames(data, img);
	set_tex_img(data, texture);
	ft_raycast(data);
	ft_mlx_hooks(data);
}
