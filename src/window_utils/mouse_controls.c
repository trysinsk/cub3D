/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:33:37 by mevonuk           #+#    #+#             */
/*   Updated: 2024/06/03 08:54:05 by trysinsk         ###   ########.fr       */
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
		interact(core);
	if (button == MOUSE_WHEEL_UP)
		core->fov += 10;
	if (button == MOUSE_WHEEL_DOWN)
		core->fov -= 10;
	if (core->fov < 30)
		core->fov = 30;
	if (core->fov > 120)
		core->fov = 120;
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
