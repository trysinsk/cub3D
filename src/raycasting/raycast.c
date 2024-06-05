/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:58:56 by mevonuk           #+#    #+#             */
/*   Updated: 2024/05/29 14:01:58 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// calculate the horizontal intercept (moiving up or down)
double	horizontal_inter(t_core *core, double angle)
{
	double	ay;
	double	ax;
	double	delta_x;
	double	delta_y;

	ay = floor((core->player->player_y / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
	delta_x = core->ray->x_dir * fabs(TILE_SIZE / tan(angle));
	delta_y = TILE_SIZE;
	if (angle > 0 && angle < PI)
	{
		ay = floor((core->player->player_y / TILE_SIZE)) * TILE_SIZE - .0001;
		delta_y = -1 * TILE_SIZE;
	}
	ax = core->player->player_x + core->ray->x_dir
		* fabs((core->player->player_y - ay) / tan(angle));
	while (in_bounds(ax, ay, core) == 0 && in_wall(ax, ay, core) != 1)
	{
		ax = ax + delta_x;
		ay = ay + delta_y;
	}
	core->ray->ax = ax;
	core->ray->pxh = ax;
	core->ray->pyh = ay;
	core->ray->flag = 0;
	return (distance(ax - core->player->player_x, ay - core->player->player_y));
}

// calculate the vertical intercept (moving right or left)
double	vertical_inter(t_core *core, double angle)
{
	double	ay;
	double	ax;
	double	delta_x;
	double	delta_y;

	ax = floor((core->player->player_x / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
	delta_y = core->ray->y_dir * fabs(TILE_SIZE * tan(angle));
	delta_x = TILE_SIZE;
	if (angle > PI / 2 && angle < 3 * PI / 2)
	{
		ax = floor((core->player->player_x / TILE_SIZE)) * TILE_SIZE - .0001;
		delta_x = -1 * TILE_SIZE;
	}
	ay = core->player->player_y + core->ray->y_dir
		* fabs((core->player->player_x - ax) * tan(angle));
	while (in_bounds(ax, ay, core) == 0 && in_wall(ax, ay, core) != 1)
	{
		ax = ax + delta_x;
		ay = ay + delta_y;
	}
	core->ray->ay = ay;
	core->ray->pxv = ax;
	core->ray->pyv = ay;
	return (distance(ax - core->player->player_x, ay - core->player->player_y));
}

// cast rays to calculate the distance to the wall
void	raycast_loop(t_core *core)
{
	int		i;
	double	dist_v;
	double	dist;
	double	delta_r;

	core->ray->angle = core->player->angle + (FOV * PI / 180 / 2);
	delta_r = FOV * PI / 180 / S_W;
	i = -1;
	while (++i < S_W)
	{
		core->ray->angle = normalize_angle(core->ray->angle);
		set_ray_direction(core, core->ray->angle);
		dist = S_H * TILE_SIZE;
		dist_v = dist;
		dist = horizontal_inter(core, core->ray->angle);
		dist_v = vertical_inter(core, core->ray->angle);
		if (dist_v < dist)
		{
			dist = dist_v;
			core->ray->flag = 1;
		}
		dist = dist * cos(core->ray->angle - core->player->angle);
		insert_column(core, i, height_of_wall(dist), core->ray->angle);
		core->ray->angle -= delta_r;
	}
}
