/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:18:12 by mevonuk           #+#    #+#             */
/*   Updated: 2024/06/06 13:17:08 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player(t_core *core)
{
	core->player = (t_player *)malloc(sizeof(t_player));
	if (!core->player)
	{
		free(core->data);
		free(core);
		ft_quit("error: allocation failed\n", core);
	}
	core->player->up_down = 0;
	core->player->left_right = 0;
	core->player->rotation = 0;
	core->player->mouse_x = 0;
	core->player->bomb_count = 0;
}

void	init_ray(t_core *core)
{
	core->fov = 60;
	core->bomb.h_flag = 0;
	core->ray = (t_ray *)malloc(sizeof(t_ray));
	if (!core->ray)
	{
		free(core->data);
		free(core->player);
		free(core);
		ft_quit("error: allocation failed\n,", core);
	}
}

void	init_color(t_core *core)
{
	core->data->c.r = -1;
	core->data->c.g = 0;
	core->data->c.b = 0;
	core->data->f.r = -1;
	core->data->f.g = 0;
	core->data->f.b = 0;
}

void	init_data(t_core **core)
{
	*core = (t_core *)malloc(1 * sizeof(t_core));
	if (!core)
		ft_quit("error: allocation failed\n", *core);
	(*core)->data = (t_data *)malloc(sizeof(t_data));
	if (!(*core)->data)
	{
		free(*core);
		ft_quit("error: allocation failed\n", *core);
	}
	else
	{
		(*core)->data->map = NULL;
		(*core)->data->no = NULL;
		(*core)->data->so = NULL;
		(*core)->data->we = NULL;
		(*core)->data->ea = NULL;
		init_color(*core);
	}
	init_player(*core);
	init_ray(*core);
	(*core)->data->height = -1;
	(*core)->data->width = -1;
	(*core)->data->player_x = -1;
	(*core)->data->player_y = -1;
	(*core)->map = 0;
}
