/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wormhole.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:14:38 by mevonuk           #+#    #+#             */
/*   Updated: 2024/06/06 14:15:00 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_wormholes(t_core *core, int y, int x, char c)
{
	if (c == 'h')
	{
		core->bomb.xh1 = x
			* TILE_SIZE + TILE_SIZE / 2;
		core->bomb.yh1 = y
			* TILE_SIZE + TILE_SIZE / 2;
	}
	if (c == 'H')
	{
		core->bomb.xh2 = x
			* TILE_SIZE + TILE_SIZE / 2;
		core->bomb.yh2 = y
			* TILE_SIZE + TILE_SIZE / 2;
	}
}

void	init_wormhole(t_core *core)
{
	core->bomb.hole.ptr = mlx_xpm_file_to_image(core->mlx,
			"./src/textures/drwho.xpm", &(core->bomb.hole).width,
			&core->bomb.hole.height);
	core->bomb.hole.data = (int *)mlx_get_data_addr(core->bomb.hole.ptr,
			&core->bomb.hole.bpp, &core->bomb.hole.size_l,
			&core->bomb.hole.endian);
}

void	check_wormhole(t_core *core)
{
	int	x;
	int	y;

	x = floor(core->player->player_x / TILE_SIZE);
	y = floor(core->player->player_y / TILE_SIZE);
	if (core->bomb.h_flag == 0
		&& (core->data->map[y][x] == 'h' || core->data->map[y][x] == 'H'))
	{
		core->bomb.h_flag = 1;
		if (core->data->map[y][x] == 'h')
		{
			core->player->player_x = core->bomb.xh2;
			core->player->player_y = core->bomb.yh2;
		}
		else if (core->data->map[y][x] == 'H')
		{
			core->player->player_x = core->bomb.xh1;
			core->player->player_y = core->bomb.yh1;
		}
	}
	if (core->bomb.h_flag == 1
		&& (core->data->map[y][x] != 'h' && core->data->map[y][x] != 'H'))
	{
		core->bomb.h_flag = 0;
	}
}
