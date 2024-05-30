/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:56:47 by mevonuk           #+#    #+#             */
/*   Updated: 2024/05/29 16:45:04 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	height_of_wall(double dist)
{
	double	height;
	double	d_to_p;

	d_to_p = S_W / 2 / tan(FOV * PI / 180 / 2);
	height = d_to_p * TILE_SIZE / dist;
	return ((int)(height));
}

int	get_counter(t_core *core, double c2)
{
	int		counter;
	int		x_off;

	if (core->ray->flag == 0)
		x_off = core->ray->ax % TILE_SIZE;
	else
		x_off = core->ray->ay % TILE_SIZE;
	counter = ((int)c2 * core->img_e.size_l
			+ x_off * (core->img_e.bpp / 8)) / 4;
	return (counter);
}

int	in_door(t_core *core)
{
	int	i;
	int	j;

	if (core->ray->flag == 0)
	{
		i = floor(core->ray->pxh / TILE_SIZE);
		j = floor(core->ray->pyh / TILE_SIZE);
	}
	else
	{
		i = floor(core->ray->pxv / TILE_SIZE);
		j = floor(core->ray->pyv / TILE_SIZE);
	}
	if (core->data->map[j][i] == '2')
		return (1);
	return (0);
}

int	get_pixel(t_core *core, double angle, double c2)
{
	int	counter;

	counter = get_counter(core, c2);
	if (in_door(core) == 1)
		return (core->img_door.data[counter]);
	if (core->ray->flag == 1)
	{
		if (angle > PI / 2 && angle < 3 * PI / 2)
			return (core->img_w.data[counter]);
		else
			return (core->img_e.data[counter]);
	}
	else
	{
		if (angle > 0 && angle < PI)
			return (core->img_n.data[counter]);
		else
			return (core->img_s.data[counter]);
	}
}

// insert a column onto the image
void	insert_column(t_core *core, int x, int height, double angle)
{
	int		count_h;
	int		color;
	int		top;
	double	scale;
	double	c2;

	count_h = S_H / 2 - height / 2;
	top = S_H / 2 + height / 2;
	if (count_h < 0)
	{
		count_h = 0;
		top = S_H;
	}
	scale = (double)TILE_SIZE / (double)height;
	c2 = 0;
	if (height > S_H)
		c2 = (height - S_H) / 2 * scale;
	while (count_h < top)
	{
		color = get_pixel(core, angle, c2);
		img_pix_put(core, x, count_h, color);
		count_h++;
		c2 += scale;
	}
}
