/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:17:04 by trysinsk          #+#    #+#             */
/*   Updated: 2024/06/03 09:39:10 by trysinsk         ###   ########.fr       */
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
	if (i < 0 || j < 0 || j >= core->data->height || i >= (int)ft_strlen(core->data->map[j]))
		return (0);
	if (core->data->map[j][i] == '1' || core->data->map[j][i] == '2'
		|| core->data->map[j][i] == '4' || core->data->map[j][i] == 'B'
		|| core->data->map[j][i] == 'X' || core->data->map[j][i] == 'T'
		|| core->data->map[j][i] == 'H' || core->data->map[j][i] == 'h')
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

void	set_ray_direction(t_core *core, double angle)
{
	core->ray->y_dir = 1;
	if (angle > 0 && angle < PI)
		core->ray->y_dir = -1;
	core->ray->x_dir = 1;
	if (angle > PI / 2 && angle < 3 * PI / 2)
		core->ray->x_dir = -1;
}

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > 2 * PI)
		angle -= (2 * PI);
	return (angle);
}
