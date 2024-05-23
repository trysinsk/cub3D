/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:17:04 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/23 14:40:12 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int hit_wall(float x, float y, t_core *core)
{
    int pos_x;
    int pos_y;

    if (x < 0 || y < 0)
        return (1);
    pos_x = floor (x / TILE_SIZE);
    pos_y = floor (y / TILE_SIZE);
    if (pos_y >= core->data->height || pos_x >= core->data->width)
        return (1);
    if (core->data->map[pos_y] && x <= (int)ft_strlen(core->data->map[pos_y]))
        {
            if (core->data->map[pos_y][pos_x] == '1')
                return (0);
        }
    return (1);
}

double get_y_wall(t_core *core)
{
    float   inter_x;
    float   inter_y;
    float   step_x;
    float   step_y;
    int     adjust;

    inter_y = floor((core->player->player_y / TILE_SIZE)) * TILE_SIZE;
    step_y = TILE_SIZE;
    inter_x = (core->player->player_x) + (inter_y - core->player->player_y) / tan(core->ray->ray_angle);
    step_x = TILE_SIZE / tan(core->ray->ray_angle);
    adjust = 1;
    if (core->ray->ray_angle > 0 && core->ray->ray_angle < PI)
    {
        inter_y += TILE_SIZE;
        adjust = -1;
    }
    else
        step_y *= -1;
    while (!hit_wall(inter_x, inter_y - adjust, core))
    {
        inter_y += step_y;
        inter_x += step_x;
    }
    return (sqrt(pow(inter_x - core->player->player_x, 2) + pow(inter_y - core->player->player_y, 2)));
}

double get_x_wall(t_core *core)
{
    float   inter_x;
    float   inter_y;
    float   step_x;
    float   step_y;
    int     adjust;

    inter_x = floor((core->player->player_x / TILE_SIZE)) * TILE_SIZE;
    step_x = TILE_SIZE;
    inter_y = (core->player->player_y) + (inter_x - core->player->player_x) / tan(core->ray->ray_angle);
    step_y = TILE_SIZE / tan(core->ray->ray_angle);
    adjust = 1;
    if (core->ray->ray_angle > (PI / 2) && core->ray->ray_angle < (3 * PI / 2))
    {
        inter_x += TILE_SIZE;
        adjust = -1;
    }
    else
        step_y *= -1;
    while (!hit_wall(inter_x, inter_y - adjust, core))
    {
        inter_y += step_y;
        inter_x += step_x;
    }
    return (sqrt(pow(inter_x - core->player->player_x, 2) + pow(inter_y - core->player->player_y, 2)));
}

void	raycast_loop(t_core *core)
{
    double  y;
    double  x;
	int     i;

	i = 0;
    core->ray->ray_angle = core->player->angle - (core->player->an_rad / 2);
	while (i < S_W)
	{
		core->ray->flag_wall = 0;
        if (core->ray->ray_angle < 0)
            core->ray->ray_angle += (2 * PI);
        if (core->ray->ray_angle > (2 * PI))
            core->ray->ray_angle -= (2 * PI);
		y = get_y_wall(core);
        x = get_x_wall(core);
        printf ("%f  %f\n", y, x);
		i++;
        core->ray->ray_angle += core->player->an_rad / S_W;
	}
}