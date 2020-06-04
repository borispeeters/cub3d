/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_title.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/23 12:59:31 by bpeeters       #+#    #+#                */
/*   Updated: 2020/02/28 16:33:10 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include "libft.h"

void		cat_title_res(t_data *data, char *title)
{
	char	*width;
	char	*height;

	width = ft_itoa(data->screenwidth);
	height = ft_itoa(data->screenheight);
	title[0] = '\0';
	ft_strlcat(title, width, 12);
	ft_strlcat(title, " x ", 12);
	ft_strlcat(title, height, 12);
	free(width);
	free(height);
}
