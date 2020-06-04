/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 17:36:11 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/02 09:42:28 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_isvalidmap(int c)
{
	if (c == '0' || c == '1' || c == '2')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int		ft_isspace(int c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int		ft_atoi_ref(char **str)
{
	long long	ans;
	int			ncheck;

	ans = 0;
	ncheck = 1;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '-')
		ncheck = -1;
	if (**str == '+' || **str == '-')
		(*str)++;
	while (**str >= '0' && **str <= '9')
	{
		if (ans * 10 + **str - '0' < ans)
		{
			ans = (-1 * ncheck - 1) / 2;
			return (ans * ncheck);
		}
		ans *= 10;
		ans += **str - '0';
		(*str)++;
	}
	return (ans * ncheck);
}

void	check_eol(char **str, t_data *data)
{
	while (**str)
	{
		if (!ft_isspace(**str))
			error_exit("Invalid character at the end of the line", data);
		(*str)++;
	}
}

void	skip_space(char **str)
{
	while (**str && ft_isspace(**str))
		++(*str);
}
