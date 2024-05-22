/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:32:14 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/22 17:08:00 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_is_not_element(char c)
{
	if (c != '1' && c != '0' && c != ' ' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W' && c != '\n')
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
	}
	else
		return (1);
    /*if (c == 'N')
        core->player->angle = idk_for_now;
    else if (c == 'S')
        core->player->angle = idk_for_now;
    else if (c == 'E')
        core->player->angle = idk_for_now;
    else if (c == 'W')
        core->player->angle = idk_for_now;*/
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
