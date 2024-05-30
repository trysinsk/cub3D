/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:00:02 by mevonuk           #+#    #+#             */
/*   Updated: 2024/05/29 17:00:30 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_left(t_core *core)
{
	core->player->angle += ROTATION_SPEED;
	core->player->angle = normalize_angle(core->player->angle);
}

void	rotate_right(t_core *core)
{
	core->player->angle -= ROTATION_SPEED;
	core->player->angle = normalize_angle(core->player->angle);
}

// take in the mouse value and call the shift, zoom or reset appropriately
int	mouse_on(int button, int x, int y, t_core *core)
{
	printf("on button %d angle: %f, %d, %d\n", button, core->player->angle, x, y);
	if (button == MOUSE_BTN_L)
		core->player->rotation = -1;
	if (button == MOUSE_BTN_R)
		core->player->rotation = 1;
	return (0);
}

int	mouse_off(int button, int x, int y, t_core *core)
{
	printf("off button %d, %d, %d\n", button, x, y);
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
		core->player->angle -=  ROTATION_SPEED;
	else
		core->player->angle +=  ROTATION_SPEED;
	core->player->mouse_x = x;
	return (0);
}