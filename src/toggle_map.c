/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:43:04 by mevonuk           #+#    #+#             */
/*   Updated: 2024/05/30 14:43:51 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	count_h = py - 2;
	while (++count_h < py + 2)
	{
		count_w = px - 2;
		while (++count_w < px + 2)
			img_pix_put(core, count_w, count_h, color);
	}
}

void	toggle_map(t_core *core)
{
	int		count_h;
	int		count_w;
	int		color;
	int		scale;

	count_h = -1;
	scale = 10;
	while (++count_h < core->data->height * scale)
	{
		count_w = -1;
		while (++count_w < (core->data->width - 1) * scale)
		{
			color = create_trgb(1, 0, 0, 0);
			if (core->data->map[count_h / scale][count_w / scale] == '1')
				color = create_trgb(1, 255, 255, 255);
			if (core->data->map[count_h / scale][count_w / scale] == '3')
				color = create_trgb(1, 100, 10, 100);
			if (core->data->map[count_h / scale][count_w / scale] == '2')
				color = create_trgb(1, 200, 20, 200);
			img_pix_put(core, count_w, count_h, color);
		}
	}
	plot_position(core, scale);
}
