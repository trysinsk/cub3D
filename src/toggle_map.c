/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:43:04 by mevonuk           #+#    #+#             */
/*   Updated: 2024/06/03 13:41:54 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	color_2d_map(t_core *core, int count_h, int count_w, int scale)
{
	int	i;
	int	j;

	i = count_w / scale;
	j = count_h / scale;
	if (i < 0 || i >= (int)ft_strlen(core->data->map[j])
		|| j < 0 || j >= core->data->height)
		return (create_trgb(1, 1, 1, 1));
	if (core->data->map[j][i] == '1')
		return (create_trgb(1, 255, 255, 255));
	if (core->data->map[j][i] == '3')
		return (create_trgb(1, 100, 10, 100));
	if (core->data->map[j][i] == '2')
		return (create_trgb(1, 200, 20, 200));
	if (core->data->map[j][i] == '4')
		return (create_trgb(1, 120, 120, 120));
	if (core->data->map[j][i] == 'B')
		return (create_trgb(1, 255, 0, 0));
	if (core->data->map[j][i] == 'X')
		return (create_trgb(1, 0, 255, 0));
	if (core->data->map[j][i] == 'T')
		return (create_trgb(1, 0, 0, 255));
	return (create_trgb(1, 1, 1, 1));
}

void	plot_direction(t_core *core, int i, double angle)
{
	double	px;
	double	py;
	int		color;
	int		count_h;
	int		count_w;

	if (angle < 0)
		angle += (2 * PI);
	else if (angle > (2 * PI))
		angle -= (2 * PI);
	px = cos(angle);
	py = -sin(angle);
	px *= i * 10;
	py *= i * 10;
	px = (core->player->player_x + floor(px)) * 10 / TILE_SIZE;
	py = (core->player->player_y + floor(py)) * 10 / TILE_SIZE;
	color = create_trgb(1, 255, 120, 120);
	count_h = py - 1;
	while (++count_h < py + 1)
	{
		count_w = px - 1;
		while (++count_w < px + 1)
			img_pix_put(core, count_w, count_h, color);
	}
}

void	plot_bombs(t_core *core, int scale)
{
	int	i;
	int	j;
	int	b;
	int	r;

	b = -1;
	r = 5;
	while (++b < core->player->bomb_count)
	{
		i = -1;
		while (++i < 2 * r)
		{
			j = -1;
			while (++j < 2 * r)
			{
				if (((i - r) * (i - r) + (j - r) * (j - r)) < r * r)
					img_pix_put(core, j + b * 12,
						i + core->data->height * scale + 1,
						create_trgb(1, 255, 0, 0));
			}
		}
	}
}

void	plot_position(t_core *core, int scale)
{
	int	px;
	int	py;
	int	color;
	int	count_h;
	int	count_w;

	px = (int)(core->player->player_x * scale / TILE_SIZE);
	py = (int)(core->player->player_y * scale / TILE_SIZE);
	color = create_trgb(1, 255, 0, 0);
	count_h = py - 3;
	while (++count_h < py + 3)
	{
		count_w = px - 3;
		while (++count_w < px + 3)
			img_pix_put(core, count_w, count_h, color);
	}
	if (core->player->bomb_count > 0)
		plot_bombs(core, scale);
}

void	toggle_map(t_core *core)
{
	int		count_h;
	int		count_w;
	int		color;
	int		scale;
	int		i;

	count_h = -1;
	scale = 10;
	while (++count_h < core->data->height * scale)
	{
		count_w = -1;
		while (++count_w < (core->data->width - 1) * scale)
		{
			color = color_2d_map(core, count_h, count_w, scale);
			img_pix_put(core, count_w, count_h, color);
		}
	}
	plot_position(core, scale);
	i = 0;
	while (i < 8)
	{
		plot_direction(core, i, core->player->angle + (30 * PI / 180));
		plot_direction(core, i, core->player->angle - (30 * PI / 180));
		i++;
	}
}
