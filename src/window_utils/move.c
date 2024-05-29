/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:00:11 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/29 11:50:14 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    move_up(t_core *core)
{
    double xd;
    double yd;

    xd = cos(core->player->angle) * PLAYER_SPEED;
    yd = -sin(core->player->angle) * PLAYER_SPEED;
    /*if (core->player->angle >= (PI /2) && core->player->angle < (3 * PI / 2))
            xd *= -1;*/
    printf ("angle: %f xd: %f yd: %f\n", core->player->angle, xd, yd);
    printf ("old posx: %f old posy: %f\n", core->player->player_x, core->player->player_y);
    core->player->player_x += xd;
    core->player->player_y += yd;
    printf ("new posx: %f new posy: %f\n", core->player->player_x, core->player->player_y);
}

void    move_down(t_core *core)
{
    double xd;
    double yd;

    xd = -cos(core->player->angle) * PLAYER_SPEED;
    yd = sin(core->player->angle) * PLAYER_SPEED;
    printf ("angle: %f xd: %f yd: %f\n", core->player->angle, xd, yd);
    printf ("old posx: %f old posy: %f\n", core->player->player_x, core->player->player_y);
    core->player->player_x += xd;
    core->player->player_y += yd;
    printf ("new posx: %f new posy: %f\n", core->player->player_x, core->player->player_y);
}
void    move_right(t_core *core)
{
    double xd;
    double yd;

    xd = sin(core->player->angle) * PLAYER_SPEED;
    yd = cos(core->player->angle) * PLAYER_SPEED;
    printf ("angle: %f xd: %f yd: %f\n", core->player->angle, xd, yd);
    printf ("old posx: %f old posy: %f\n", core->player->player_x, core->player->player_y);
    core->player->player_x += xd;
    core->player->player_y += yd;
    printf ("new posx: %f new posy: %f\n", core->player->player_x, core->player->player_y);
}

void    move_left(t_core *core)
{
    double xd;
    double yd;

    xd = -sin(core->player->angle) * PLAYER_SPEED;
    yd = -cos(core->player->angle) * PLAYER_SPEED;
    printf ("angle: %f xd: %f yd: %f\n", core->player->angle, xd, yd);
    printf ("old posx: %f old posy: %f\n", core->player->player_x, core->player->player_y);
    core->player->player_x += xd;
    core->player->player_y += yd;
    printf ("new posx: %f new posy: %f\n", core->player->player_x, core->player->player_y);
}

void    rotate_left(t_core *core)
{
    printf("current angle: %f\n", core->player->angle);
    core->player->angle += ROTATION_SPEED;
    core->player->angle = normalize_angle(core->player->angle);
    printf("new angle: %f\n", core->player->angle);
}

void    rotate_right(t_core *core)
{
    printf("current angle: %f\n", core->player->angle);
    core->player->angle -= ROTATION_SPEED;
    core->player->angle = normalize_angle(core->player->angle);
    printf("new angle: %f\n", core->player->angle);
}