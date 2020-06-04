/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 09:35:56 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:15:58 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_map(t_data *data, int i, int j, int k)
{
	data->map[i][k] = 0;
	if (data->arr[i][j] == '1')
		data->map[i][k] = 1;
	if (data->arr[i][j] == '2' || data->arr[i][j] == '3')
		set_sprite(data, i, k, data->arr[i][j] - '0');
	if (data->arr[i][j] == 'N')
		set_north(data, i, k);
	if (data->arr[i][j] == 'S')
		set_south(data, i, k);
	if (data->arr[i][j] == 'E')
		set_east(data, i, k);
	if (data->arr[i][j] == 'W')
		set_west(data, i, k);
}

void	fill_map(t_data *data, int y)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	data->num_sprite = 0;
	while (i < y)
	{
		j = 0;
		k = 0;
		while (data->arr[i][j] && k < data->mapwidth[i])
		{
			if (ft_isvalidmap(data->arr[i][j]))
			{
				set_map(data, i, j, k);
				k++;
			}
			else if (!ft_isspace(data->arr[i][j]))
				error_exit("Invalid character in map", data);
			j++;
		}
		i++;
	}
	if (!data->start)
		error_exit("No start position given", data);
}

void	map_parser(t_data *data)
{
	read_map(data);
	allocate_map(data);
	fill_map(data, data->mapheight);
}

void	reset_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->mapheight)
	{
		x = 0;
		while (x < data->mapwidth[y])
		{
			if (data->map[y][x] >= 10)
				data->map[y][x] -= 10;
			x++;
		}
		y++;
	}
}

void	ft_floodfill(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->mapwidth[y] || y < 0 || y >= data->mapheight)
	{
		data->map_check = -1;
		return ;
	}
	if (data->map[y][x] == 1 || data->map[y][x] >= 10)
		return ;
	data->map[y][x] += 10;
	ft_floodfill(data, x - 1, y);
	ft_floodfill(data, x + 1, y);
	ft_floodfill(data, x, y - 1);
	ft_floodfill(data, x, y + 1);
	ft_floodfill(data, x - 1, y - 1);
	ft_floodfill(data, x + 1, y + 1);
	ft_floodfill(data, x + 1, y - 1);
	ft_floodfill(data, x - 1, y + 1);
	return ;
}
