/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:17:04 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/28 16:19:03 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// check if point is inside of a wall
int	in_wall(double x, double y, t_core *core)
{
	int	i;
	int	j;

	i = floor(x / TILE_SIZE);
	j = floor(y / TILE_SIZE);
	if (core->data->mapi[i][j] == 1)
		return (1);
	return (0);
}

// calculate distance
double	distance(double x, double y)
{
	return (sqrt(x * x + y * y));
}

// check if point is within bounds of map
int	in_bounds(double x, double y, t_core *core)
{
	if (x < 0 || x > (core->data->width - 1) * TILE_SIZE)
		return (1);
	if (y < 0 || y > core->data->height * TILE_SIZE)
		return (1);
	return (0);
}

// calculate the horizontal intercept (moiving up or down)
double	horizontal_inter(t_core *core, double angle)
{
	double	ay;
	double	ax;
	double	delta_x;
	double	delta_y;
	int		x_dir;

	x_dir = 1;
	if (angle > PI / 2 && angle < 3 * PI / 2)
		x_dir = -1;
	ay = floor((core->player->player_y / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
	delta_x = x_dir * fabs(TILE_SIZE / tan(angle));
	delta_y = TILE_SIZE;
	if (angle > 0 && angle < PI)
	{
		ay = floor((core->player->player_y / TILE_SIZE)) * TILE_SIZE - .0001;
		delta_y = -1 * TILE_SIZE;
	}
	ax = core->player->player_x + x_dir
		* fabs((core->player->player_y - ay) / tan(angle));
	while (in_bounds(ax, ay, core) == 0 && in_wall(ax, ay, core) != 1)
	{
		ax = ax + delta_x;
		ay = ay + delta_y;
	}
	return (distance(ax - core->player->player_x, ay - core->player->player_y));
}

// calculate the vertical intercept (moving right or left)
double	vertical_inter(t_core *core, double angle)
{
	double	ay;
	double	ax;
	double	delta_x;
	double	delta_y;
	int		y_dir;

	y_dir = 1;
	if (angle > 0 && angle < PI)
		y_dir = -1;
	ax = floor((core->player->player_x / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
	ay = core->player->player_y + y_dir
		* fabs((core->player->player_x - ax) * tan(angle));
	delta_x = TILE_SIZE;
	delta_y = y_dir * fabs(TILE_SIZE * tan(angle));
	if (angle > PI / 2 && angle < 3 * PI / 2)
	{
		ax = floor((core->player->player_x / TILE_SIZE)) * TILE_SIZE - .0001;
		delta_x = -1 * TILE_SIZE;
	}
	while (in_bounds(ax, ay, core) == 0 && in_wall(ax, ay, core) != 1)
	{
		ax = ax + delta_x;
		ay = ay + delta_y;
	}
	return (distance(ax - core->player->player_x, ay - core->player->player_y));
}

int	height_of_wall(double dist)
{
	double	height;
	double	d_to_p;

	d_to_p = S_W / 2 / tan(FOV * PI / 180 / 2);
	height = d_to_p * TILE_SIZE / dist;
	return ((int)(height));
}

// insert a column onto the image
void	insert_column(t_core *core, int x, int height)
{
	int	count_h;
	int	color;
	int	top;
	int	counter;

	count_h = S_H / 2 - height / 2;
	top = S_H / 2 + height / 2;
	if (count_h < 0)
	{
		count_h = 0;
		top = S_H;
	}
	while (count_h < top)
	{
		counter = (height / 64 * (x % 64 + count_h * 64)) % (64 * 64);
		color = core->img_n.data[counter];
		img_pix_put(core, x, count_h, color);
		count_h++;
	}
}

// cast rays to calculate the distance to the wall
void	raycast_loop(t_core *core)
{
	int		i;
	double	dist_v;
	double	dist;
	double	delta_r;
	double	angle;

	angle = core->player->angle - (FOV * PI / 180 / 2);
	delta_r = FOV * PI / 180 / S_W;
	i = 1;
	while (i <= S_W)
	{
		dist = S_H * TILE_SIZE;
		dist_v = dist;
		dist = horizontal_inter(core, angle);
		dist_v = vertical_inter(core, angle);
		if (dist_v < dist)
			dist = dist_v;
		dist = dist * cos(angle - core->player->angle);
		insert_column(core, S_W - i, height_of_wall(dist));
		i++;
		angle += delta_r;
	}
}
