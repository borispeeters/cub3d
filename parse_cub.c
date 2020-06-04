/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 09:41:38 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:20:59 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include "get_next_line.h"
#include <stdlib.h>

static void	init_cub(t_data *data)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		data->type_check[i] = 0;
		i++;
	}
	i = 0;
	while (i < 5)
	{
		data->path[i] = NULL;
		i++;
	}
	data->arr = NULL;
	data->screenwidth = -1;
	data->screenheight = -1;
	data->floor = -1;
	data->ceiling = -1;
	data->map_check = 0;
	data->num_sprite = 0;
	data->mapheight = 0;
	data->start = 0;
	data->status = 0;
}

static int	parse_data(char *str, t_data *data)
{
	while (*str)
	{
		if (*str == 'R')
			return (parse_res(&str, data));
		if (*str == 'N' && *(str + 1) == 'O')
			return (parse_path(data, &str, &data->path[0], 1));
		if (*str == 'S' && *(str + 1) == 'O')
			return (parse_path(data, &str, &data->path[1], 2));
		if (*str == 'E' && *(str + 1) == 'A')
			return (parse_path(data, &str, &data->path[2], 3));
		if (*str == 'W' && *(str + 1) == 'E')
			return (parse_path(data, &str, &data->path[3], 4));
		if (*str == 'S')
			return (parse_path(data, &str, &data->path[4], 5));
		if (*str == 'F')
			return (parse_color(data, &str, &data->floor, 6));
		if (*str == 'C')
			return (parse_color(data, &str, &data->ceiling, 7));
		else if (!ft_isspace(*str))
			error_exit("Invalid type identifier", data);
		str++;
	}
	return (0);
}

static void	cub_parser(char *cub, t_data *data)
{
	int		ret;
	char	*line;

	ret = 1;
	data->fd = open(cub, O_RDONLY);
	if (data->fd == -1)
		error_exit("Failed to open file", data);
	while (ret > 0)
	{
		ret = get_next_line(data->fd, &line);
		data->map_check += parse_data(line, data);
		if (ret >= 0)
		{
			free(line);
			line = NULL;
		}
		if (data->map_check == 8)
			break ;
	}
}

static void	check_cub(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (*str)
		str++;
	str--;
	if (*str != 'b')
		error_exit("First argument is not a .cub file", data);
	str--;
	if (*str != 'u')
		error_exit("First argument is not a .cub file", data);
	str--;
	if (*str != 'c')
		error_exit("First argument is not a .cub file", data);
	str--;
	if (*str != '.')
		error_exit("First argument is not a .cub file", data);
}

void		parse_hub(t_data *data, char *cub)
{
	check_cub(cub, data);
	init_cub(data);
	cub_parser(cub, data);
	map_parser(data);
	ft_floodfill(data, data->posx, data->posy);
	reset_map(data);
	if (data->map_check == -1)
		error_exit("Invalid map", data);
}
