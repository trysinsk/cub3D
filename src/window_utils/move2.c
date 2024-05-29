/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:05:24 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/29 16:48:16 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_in_wall(t_core *core, double pos, char c)
{
	double	new_pos;
	int		x;
	int		y;

	if (pos < 0)
		pos -= WALL_BUFFER;
	else
		pos += WALL_BUFFER;
	if (c == 'x')
	{
		new_pos = core->player->player_x + pos;
		x = floor(new_pos / TILE_SIZE);
		y = floor(core->player->player_y / TILE_SIZE);
		if (core->data->map[y][x] == '1')
			return (1);
	}
	else if (c == 'y')
	{
		new_pos = core->player->player_y + pos;
		x = floor(core->player->player_x / TILE_SIZE);
		y = floor(new_pos / TILE_SIZE);
		if (core->data->map[y][x] == '1')
			return (1);
	}
	return (0);
}

void	move_player(t_core *core)
{
	if (core->player->up_down == 1)
		move_up(core);
	if (core->player->up_down == -1)
		move_down(core);
	if (core->player->left_right == -1)
		move_right(core);
	if (core->player->left_right == 1)
		move_left(core);
	if (core->player->rotation == 1)
		rotate_right(core);
	if (core->player->rotation == -1)
		rotate_left(core);
}
