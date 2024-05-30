/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:05:24 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/30 10:15:43 by trysinsk         ###   ########.fr       */
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
		if (core->data->map[y][x] == '1' || core->data->map[y][x] == '2')
			return (1);
	}
	else if (c == 'y')
	{
		new_pos = core->player->player_y + pos;
		x = floor(core->player->player_x / TILE_SIZE);
		y = floor(new_pos / TILE_SIZE);
		if (core->data->map[y][x] == '1' || core->data->map[y][x] == '2')
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

void	toggle_door(t_core *core)
{
	double	xd;
	double	yd;
	int		new_pos_x;
	int		new_pos_y;

	xd = cos(core->player->angle) * PLAYER_SPEED;
	yd = -sin(core->player->angle) * PLAYER_SPEED;
	if (xd < 0)
		xd -= ILLUSION_BUFFER;
	else
		xd += ILLUSION_BUFFER;
	if (yd < 0)
		yd -= ILLUSION_BUFFER;
	else
		yd += ILLUSION_BUFFER;
	new_pos_x = floor((core->player->player_x + xd) / TILE_SIZE);
	new_pos_y = floor((core->player->player_y + yd) / TILE_SIZE);
	if (new_pos_x != floor(core->player->player_x / TILE_SIZE)
		|| new_pos_y != floor(core->player->player_y / TILE_SIZE))
	{
		if (core->data->map[new_pos_y][new_pos_x] == '2')
			core->data->map[new_pos_y][new_pos_x] = '3';
		else if (core->data->map[new_pos_y][new_pos_x] == '3')
			core->data->map[new_pos_y][new_pos_x] = '2';
	}
}
