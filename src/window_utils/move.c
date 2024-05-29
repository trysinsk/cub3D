/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:00:11 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/29 10:04:47 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    move_up(t_core *core)
{
    double xd;
    double yd;

    xd = -cos(core->player->angle) * PLAYER_SPEED;
    yd = -sin(core->player->angle) * PLAYER_SPEED;
    printf ("angle: %f xd: %f yd: %f\n", core->player->angle, xd, yd);
    core->player->player_x += xd;
    core->player->player_y += yd;
}

void    move_down(t_core *core)
{
    double xd;
    double yd;

    xd = cos(core->player->angle) * PLAYER_SPEED;
    yd = sin(core->player->angle) * PLAYER_SPEED;
    printf ("angle: %f xd: %f yd: %f\n", core->player->angle, xd, yd);
    core->player->player_x += xd;
    core->player->player_y += yd;
}

void    move_right(t_core *core)
{
    double xd;
    double yd;

    xd = sin(core->player->angle) * PLAYER_SPEED;
    yd = -cos(core->player->angle) * PLAYER_SPEED;
    printf ("angle: %f xd: %f yd: %f\n", core->player->angle, xd, yd);
    core->player->player_x += xd;
    core->player->player_y += yd;
}

void    move_left(t_core *core)
{
    double xd;
    double yd;

    xd = -sin(core->player->angle) * PLAYER_SPEED;
    yd = cos(core->player->angle) * PLAYER_SPEED;
    printf ("angle: %f xd: %f yd: %f\n", core->player->angle, xd, yd);
    core->player->player_x += xd;
    core->player->player_y += yd;
}