/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:32:14 by trysinsk          #+#    #+#             */
/*   Updated: 2024/06/06 13:41:16 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_atoi_color(const char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	if (!nptr)
		return (256);
	while (nptr && nptr[i] != '\0'
		&& (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr && (nptr[i] == '+' || nptr[i] == '-'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr != NULL && ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * nb);
}

int	ft_is_not_element(char c)
{
	if (c != '1' && c != '0' && c != ' ' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W' && c != '\n' && c != '2'
		&& c != '4' && c != 'B' && c != 'X' && c != 'T')
		return (1);
	else
		return (0);
}

int	ft_is_player_pos(char c, t_core *core, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		core->data->player_x = x;
		core->data->player_y = y;
		core->player->player_x = core->data->player_x
			* TILE_SIZE + TILE_SIZE / 2;
		core->player->player_y = core->data->player_y
			* TILE_SIZE + TILE_SIZE / 2;
	}
	else
		return (1);
	if (c == 'N')
		core->player->angle = PI / 2;
	else if (c == 'S')
		core->player->angle = (3 * PI) / 2;
	else if (c == 'E')
		core->player->angle = 0;
	else if (c == 'W')
		core->player->angle = PI;
	else
		return (1);
	core->player->an_rad = (core->fov * PI) / 180;
	return (0);
}

int	ft_check_num_var(t_core *core)
{
	int	x;
	int	y;
	int	player;

	player = 0;
	y = 0;
	while (core->data->map[y])
	{
		x = 0;
		while (core->data->map[y][x] != '\0')
		{
			if (ft_is_not_element(core->data->map[y][x]) == 1)
				return (1);
			if (ft_is_player_pos(core->data->map[y][x], core, y, x) == 0)
				player++;
			x++;
		}
		y++;
	}
	if (player != 1)
	{
		printf ("error: too many players\n");
		return (1);
	}
	return (0);
}

int	ft_map_validation(t_core *core)
{
	if (ft_check_num_var(core) != 0)
		return (1);
	if (ft_check_outer_walls(core, core->data->map, 0, 0) != 0)
		return (1);
	if (ft_check_spaces(core, core->data->map, 0, 0) != 0)
		return (1);
	return (0);
}
