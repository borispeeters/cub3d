/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   store_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 08:47:32 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:38:46 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <stdlib.h>

void		allocate_map(t_data *data)
{
	int	i;
	int	j;

	allocate_map_height(data);
	i = 0;
	while (i < data->mapheight)
	{
		j = 0;
		data->mapwidth[i] = 0;
		while (data->arr[i][j])
		{
			if (ft_isvalidmap(data->arr[i][j]))
			{
				if (data->arr[i][j] == '2' || data->arr[i][j] == '3')
					data->num_sprite++;
				data->mapwidth[i]++;
			}
			j++;
		}
		data->map[i] = (int*)malloc(sizeof(int) * (data->mapwidth[i]));
		if (!data->map[i])
			error_exit("Failed to allocate memory for a line in the map", data);
		i++;
	}
	allocate_sprites(data);
}

static void	realloc_map(t_data *data, int len)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = data->arr;
	data->arr = (char**)malloc(sizeof(char*) * (len + 2));
	if (!data->arr)
		error_exit("Failed to allocate memory for the temporary map", data);
	while (i < len)
	{
		data->arr[i] = ft_strdup(tmp[i]);
		if (!data->arr[i])
			error_exit("Failed to allocate memory for a line in the map", data);
		free(tmp[i]);
		i++;
	}
	data->arr[i + 1] = NULL;
	free(tmp);
}

static void	check_map_error(char *str, t_data *data)
{
	if (ft_isvalidmap(*str) && data->status == 1)
		error_exit("Empty line in map", data);
	if (!*str && data->mapheight && data->status == 0)
		data->status = 1;
	else if (*str)
		error_exit("Invalid character in .cub file", data);
}

void		read_map(t_data *data)
{
	int		ret;
	char	*line;

	ret = 1;
	while (ret > 0)
	{
		realloc_map(data, data->mapheight);
		ret = get_next_line(data->fd, &line);
		data->arr[data->mapheight] = line;
		if (!data->arr[data->mapheight])
			error_exit("Something went wrong reading the .cub file", data);
		skip_space(&line);
		if (ft_isvalidmap(*line) && data->status == 0)
		{
			data->mapheight++;
			continue ;
		}
		check_map_error(line, data);
		free(data->arr[data->mapheight]);
	}
	if (close(data->fd) == -1)
		error_exit("Failed to close the .cub file", data);
}
