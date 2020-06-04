/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 08:59:51 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:13:36 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include "libft.h"
#include <mlx.h>

void	error_exit(char *str, t_data *data)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	if (data->mlx && data->img[0]->img)
		mlx_destroy_image(data->mlx, data->img[0]->img);
	if (data->mlx && data->img[1]->img)
		mlx_destroy_image(data->mlx, data->img[1]->img);
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
	exit(0);
}
