/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 08:55:40 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:22:17 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

static void	valid_path(char **path, t_data *data)
{
	int	fd;

	if (*path == NULL)
		error_exit("Failed to allocate memory for a texture", data);
	fd = open(*path, O_RDONLY);
	if (fd == -1)
		error_exit("Invalid path or file, or failed to open file", data);
	if (close(fd) == -1)
		error_exit("Failed to close the .cub file", data);
}

int			parse_path(t_data *data, char **str, char **path, int type)
{
	size_t	len;

	if (data->type_check[type] == 1)
		error_exit("Path to texture given twice", data);
	(*str)++;
	if (type < 5)
		(*str)++;
	if (!ft_isspace(**str))
		error_exit("Key and elements should be separated by a space", data);
	(*str)++;
	skip_space(str);
	len = 0;
	while ((*str)[len] && !ft_isspace((*str)[len]))
		len++;
	*path = ft_substr(*str, 0, len);
	valid_path(path, data);
	while ((*str)[len])
	{
		if (!ft_isspace((*str)[len]))
			error_exit("Invalid character in texture path", data);
		len++;
	}
	data->type_check[type] = 1;
	return (1);
}
