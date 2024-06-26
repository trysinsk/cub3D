/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:05:24 by trysinsk          #+#    #+#             */
/*   Updated: 2024/06/05 11:13:17 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	valid_wall(char **map, int y, int x)
{
	if (map[y][x] == '1' || map[y][x] == '2' || map[y][x] == '4'
		|| map[y][x] == 'B' || map[y][x] == 'X' || map[y][x] == 'T')
		return (1);
	return (0);
}

int	is_in_wall(t_core *core, double pos, char c, char **map)
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
		if (valid_wall(map, y, x))
			return (1);
	}
	else if (c == 'y')
	{
		new_pos = core->player->player_y + pos;
		x = floor(core->player->player_x / TILE_SIZE);
		y = floor(new_pos / TILE_SIZE);
		if (valid_wall(map, y, x))
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

void	interact_object(t_core *core, int new_pos_x, int new_pos_y)
{
	if (new_pos_x != floor(core->player->player_x / TILE_SIZE)
		|| new_pos_y != floor(core->player->player_y / TILE_SIZE))
	{
		if (core->data->map[new_pos_y][new_pos_x] == '2')
			core->data->map[new_pos_y][new_pos_x] = '3';
		else if (core->data->map[new_pos_y][new_pos_x] == '3')
			core->data->map[new_pos_y][new_pos_x] = '2';
	}
	if (core->data->map[new_pos_y][new_pos_x] == 'B')
	{
		core->player->bomb_count += 1;
		core->data->map[new_pos_y][new_pos_x] = 'X';
		printf("you have %d bomb(s)\n", core->player->bomb_count);
	}
	if (core->data->map[new_pos_y][new_pos_x] == '4'
		&& core->player->bomb_count > 0)
	{
		core->player->bomb_count -= 1;
		core->data->map[new_pos_y][new_pos_x] = '0';
	}
	if (core->data->map[new_pos_y][new_pos_x] == 'T')
		on_destroy(core);
}

void	interact(t_core *core)
{
	double	xd;
	double	yd;
	int		new_pos_x;
	int		new_pos_y;

	xd = cos(core->player->angle) * PLAYER_SPEED;
	yd = -sin(core->player->angle) * PLAYER_SPEED;
	xd *= ILLUSION_BUFFER;
	yd *= ILLUSION_BUFFER;
	new_pos_x = floor((core->player->player_x + xd) / TILE_SIZE);
	new_pos_y = floor((core->player->player_y + yd) / TILE_SIZE);
	interact_object(core, new_pos_x, new_pos_y);
}
