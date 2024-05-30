/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:33:37 by mevonuk           #+#    #+#             */
/*   Updated: 2024/05/30 14:34:05 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// take in the mouse value and call the shift, zoom or reset appropriately
int	mouse_on(int button, int x, int y, t_core *core)
{
	(void)x;
	(void)y;
	if (button == MOUSE_BTN_L)
		core->player->rotation = -1;
	if (button == MOUSE_BTN_R)
		core->player->rotation = 1;
	if (button == MOUSE_WHEEL_BTN)
		toggle_door(core);
	else if (button == MOUSE_WHEEL_UP)
		move_up(core);
	else if (button == MOUSE_WHEEL_DOWN)
		move_down(core);
	return (0);
}

int	mouse_off(int button, int x, int y, t_core *core)
{
	(void)x;
	(void)y;
	if (button == MOUSE_BTN_L)
		core->player->rotation = 0;
	if (button == MOUSE_BTN_R)
		core->player->rotation = 0;
	return (0);
}

int	mouse_move(int x, int y, t_core *core)
{
	(void)y;
	if (x > core->player->mouse_x)
		rotate_right(core);
	else
		rotate_left(core);
	core->player->mouse_x = x;
	return (0);
}
