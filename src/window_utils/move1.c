/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:00:11 by trysinsk          #+#    #+#             */
/*   Updated: 2024/06/03 09:07:03 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_up(t_core *core)
{
	double	xd;
	double	yd;

	xd = cos(core->player->angle) * PLAYER_SPEED;
	yd = -sin(core->player->angle) * PLAYER_SPEED;
	if (is_in_wall(core, xd, 'x', core->data->map))
		xd = 0;
	if (is_in_wall(core, yd, 'y', core->data->map))
		yd = 0;
	core->player->player_x += xd;
	core->player->player_y += yd;
}

void	move_down(t_core *core)
{
	double	xd;
	double	yd;

	xd = -cos(core->player->angle) * PLAYER_SPEED;
	yd = sin(core->player->angle) * PLAYER_SPEED;
	if (is_in_wall(core, xd, 'x', core->data->map))
		xd = 0;
	if (is_in_wall(core, yd, 'y', core->data->map))
		yd = 0;
	core->player->player_x += xd;
	core->player->player_y += yd;
}

void	move_right(t_core *core)
{
	double	xd;
	double	yd;

	xd = sin(core->player->angle) * PLAYER_SPEED;
	yd = cos(core->player->angle) * PLAYER_SPEED;
	if (is_in_wall(core, xd, 'x', core->data->map))
		xd = 0;
	if (is_in_wall(core, yd, 'y', core->data->map))
		yd = 0;
	core->player->player_x += xd;
	core->player->player_y += yd;
}

void	move_left(t_core *core)
{
	double	xd;
	double	yd;

	xd = -sin(core->player->angle) * PLAYER_SPEED;
	yd = -cos(core->player->angle) * PLAYER_SPEED;
	if (is_in_wall(core, xd, 'x', core->data->map))
		xd = 0;
	if (is_in_wall(core, yd, 'y', core->data->map))
		yd = 0;
	core->player->player_x += xd;
	core->player->player_y += yd;
}
