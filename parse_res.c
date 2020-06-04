/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_res.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 08:54:44 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 14:25:49 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void	check_res(t_data *data)
{
	if (data->screenwidth == -1 || data->screenheight == -1)
		error_exit("Please give two numbers for the resolution", data);
	if (data->screenwidth == 0 || data->screenheight == 0)
		error_exit("Cannot have a resolution of 0", data);
}

int			parse_res(char **str, t_data *data)
{
	if (data->type_check[0] == 1)
		error_exit("Resolution given twice", data);
	(*str)++;
	if (!ft_isspace(**str))
		error_exit("Key and elements should be separated by a space", data);
	(*str)++;
	while (**str)
	{
		if (ft_isdigit(**str))
		{
			if (data->screenwidth == -1)
				data->screenwidth = ft_atoi_ref(str);
			else if (data->screenheight == -1)
				data->screenheight = ft_atoi_ref(str);
			else
				error_exit("Width and height already given in", data);
			continue;
		}
		else if (!ft_isspace(**str))
			error_exit("Invalid character in resolution", data);
		(*str)++;
	}
	check_res(data);
	data->type_check[0] = 1;
	return (1);
}
