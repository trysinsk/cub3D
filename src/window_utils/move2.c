/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:05:24 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/29 14:13:58 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    move_player(t_core *core)
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