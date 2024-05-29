/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:00:11 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/29 13:47:54 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int is_in_wall(t_core *core, double pos,  char c)
{
    double  new_pos;
    int     x;
    int     y;
    
    if (c == 'x')
    {
        printf ("pos_x: %f\n", pos);
        if (pos < 0)
            pos -= 10;
        else
            pos += 10;
        new_pos = core->player->player_x + pos;
        x = floor(new_pos / TILE_SIZE);
        y = floor(core->player->player_y / TILE_SIZE);
        if (core->data->map[y][x] == '1')
        return (1);
    }
    else if (c == 'y')
    {
        printf ("pos_y: %f\n", pos);
        if (pos < 0)
            pos -= 10;
        else
            pos += 10;
        new_pos = core->player->player_y + pos;
        x = floor(core->player->player_x / TILE_SIZE);
        y = floor(new_pos / TILE_SIZE);
        if (core->data->map[y][x] == '1')
        return (1);
    }
    return (0);
}

void    move_up(t_core *core)
{
    double xd;
    double yd;

    xd = cos(core->player->angle) * PLAYER_SPEED;
    yd = -sin(core->player->angle) * PLAYER_SPEED;
    printf ("angle: %f xd: %f yd: %f\n", core->player->angle, xd, yd);
    printf ("old posx: %f old posy: %f\n", core->player->player_x, core->player->player_y);
    if (is_in_wall(core, xd, 'x'))
        xd = 0;
    if (is_in_wall(core, yd, 'y'))
        yd = 0;
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
    if (is_in_wall(core, xd, 'x'))
        xd = 0;
    if (is_in_wall(core, yd, 'y'))
        yd = 0;
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
    if (is_in_wall(core, xd, 'x'))
        xd = 0;
    if (is_in_wall(core, yd, 'y'))
        yd = 0;
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
    if (is_in_wall(core, xd, 'x'))
        xd = 0;
    if (is_in_wall(core, yd, 'y'))
        yd = 0;
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