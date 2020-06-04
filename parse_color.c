/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_color.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 08:58:12 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:41:45 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void	parse_rgb(char **str, unsigned char *col, t_data *data)
{
	int	tmp;

	if (**str == '-')
		error_exit("Negative color value given", data);
	if (!ft_isdigit(**str))
		error_exit("Invalid character in color", data);
	tmp = ft_atoi_ref(str);
	if (tmp > 255 || tmp < 0)
		error_exit("Color value over 255", data);
	*col = tmp;
}

int			parse_color(t_data *data, char **str, int *rgb, int type)
{
	t_color	pack;

	(*str)++;
	if (!ft_isspace(**str))
		error_exit("Key and elements should be separated by a space", data);
	(*str)++;
	if (data->type_check[type] == 1)
		error_exit("Floor or ceiling color given twice", data);
	while (**str && ft_isspace(**str))
		(*str)++;
	parse_rgb(str, &pack.argb.r, data);
	if (**str != ',')
		error_exit("Color values not separated by a comma", data);
	(*str)++;
	parse_rgb(str, &pack.argb.g, data);
	if (**str != ',')
		error_exit("Color values not separated by a comma", data);
	(*str)++;
	parse_rgb(str, &pack.argb.b, data);
	check_eol(str, data);
	*rgb = pack.color & 0x00FFFFFF;
	data->type_check[type] = 1;
	return (1);
}
