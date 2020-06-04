/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:37:25 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:18:43 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include "libft.h"

static void	set_max_res(t_data *data)
{
	int	sizex;
	int	sizey;

	mlx_get_screen_size(data->mlx, &sizex, &sizey);
	if (data->screenwidth > sizex)
		data->screenwidth = sizex;
	if (data->screenheight > sizey)
		data->screenheight = sizey;
}

static void	check_second_arg(char *str, t_data *data)
{
	if (ft_strncmp(str, "--save", ft_strlen(str)) || ft_strlen(str) < 6)
		error_exit("Second argument is not '--save'", data);
}

int			main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		parse_hub(&data, argv[1]);
		set_max_res(&data);
		init_mlx(&data);
	}
	if (argc == 3)
	{
		check_second_arg(argv[2], &data);
		parse_hub(&data, argv[1]);
		write_bmp(&data);
		exit(0);
	}
	error_exit("Incorrect number of arguments", &data);
	return (0);
}
