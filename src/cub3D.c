/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:06:13 by trysinsk          #+#    #+#             */
/*   Updated: 2024/06/05 11:05:01 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cieling_floor(t_core *core)
{
	int		count_h;
	int		count_w;
	int		color;

	count_h = -1;
	while (++count_h < S_H)
	{
		count_w = -1;
		while (++count_w < S_W)
		{
			if (count_h < S_H / 2)
				color = create_trgb(1, core->data->c.r,
						core->data->c.g, core->data->c.b);
			else
				color = create_trgb(1, core->data->f.r,
						core->data->f.g, core->data->f.b);
			img_pix_put(core, count_w, count_h, color);
		}
	}
}

void	init_textures(t_core *core)
{
	core->img_n.ptr = mlx_xpm_file_to_image(core->mlx, core->data->no,
			&(core->img_n).width, &core->img_n.height);
	core->img_n.data = (int *)mlx_get_data_addr(core->img_n.ptr,
			&core->img_n.bpp, &core->img_n.size_l, &core->img_n.endian);
	core->img_s.ptr = mlx_xpm_file_to_image(core->mlx, core->data->so,
			&(core->img_s).width, &core->img_s.height);
	core->img_s.data = (int *)mlx_get_data_addr(core->img_s.ptr,
			&core->img_s.bpp, &core->img_s.size_l, &core->img_s.endian);
	core->img_e.ptr = mlx_xpm_file_to_image(core->mlx, core->data->ea,
			&(core->img_e).width, &core->img_e.height);
	core->img_e.data = (int *)mlx_get_data_addr(core->img_e.ptr,
			&core->img_e.bpp, &core->img_e.size_l, &core->img_e.endian);
	core->img_w.ptr = mlx_xpm_file_to_image(core->mlx, core->data->we,
			&(core->img_w).width, &core->img_w.height);
	core->img_w.data = (int *)mlx_get_data_addr(core->img_w.ptr,
			&core->img_w.bpp, &core->img_w.size_l, &core->img_w.endian);
	core->img_door.ptr = mlx_xpm_file_to_image(core->mlx,
			"./src/textures/door_closed.xpm", &(core->img_door).width,
			&core->img_door.height);
	core->img_door.data = (int *)mlx_get_data_addr(core->img_door.ptr,
			&core->img_door.bpp, &core->img_door.size_l,
			&core->img_door.endian);
}

void	init_bomb(t_core *core)
{
	core->bomb.full.ptr = mlx_xpm_file_to_image(core->mlx,
			"./src/textures/bomb_full.xpm", &(core->bomb.full).width,
			&core->bomb.full.height);
	core->bomb.full.data = (int *)mlx_get_data_addr(core->bomb.full.ptr,
			&core->bomb.full.bpp, &core->bomb.full.size_l,
			&core->bomb.full.endian);
	core->bomb.empty.ptr = mlx_xpm_file_to_image(core->mlx,
			"./src/textures/bomb_empty.xpm", &(core->bomb.empty).width,
			&core->bomb.empty.height);
	core->bomb.empty.data = (int *)mlx_get_data_addr(core->bomb.empty.ptr,
			&core->bomb.empty.bpp, &core->bomb.empty.size_l,
			&core->bomb.empty.endian);
	core->bomb.wall.ptr = mlx_xpm_file_to_image(core->mlx,
			"./src/textures/crumbling_peace.xpm", &(core->bomb.wall).width,
			&core->bomb.wall.height);
	core->bomb.wall.data = (int *)mlx_get_data_addr(core->bomb.wall.ptr,
			&core->bomb.wall.bpp, &core->bomb.wall.size_l,
			&core->bomb.wall.endian);
	core->bomb.t.ptr = mlx_xpm_file_to_image(core->mlx,
			"./src/textures/exit.xpm", &(core->bomb.t).width,
			&core->bomb.wall.height);
	core->bomb.t.data = (int *)mlx_get_data_addr(core->bomb.t.ptr,
			&core->bomb.t.bpp, &core->bomb.t.size_l,
			&core->bomb.t.endian);
}

int	make_image(t_core *core)
{
	core->img = mlx_new_image(core->mlx, S_W, S_H);
	core->addr = mlx_get_data_addr(core->img, &core->bpp,
			&core->line_len, &core->endian);
	init_textures(core);
	init_bomb(core);
	cieling_floor(core);
	raycast_loop(core);
	if (core->map == 1)
		toggle_map(core);
	mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
	mlx_destroy_image(core->mlx, core->img);
	mlx_destroy_image(core->mlx, core->img_n.ptr);
	mlx_destroy_image(core->mlx, core->img_s.ptr);
	mlx_destroy_image(core->mlx, core->img_e.ptr);
	mlx_destroy_image(core->mlx, core->img_w.ptr);
	mlx_destroy_image(core->mlx, core->img_door.ptr);
	mlx_destroy_image(core->mlx, core->bomb.full.ptr);
	mlx_destroy_image(core->mlx, core->bomb.empty.ptr);
	mlx_destroy_image(core->mlx, core->bomb.wall.ptr);
	mlx_destroy_image(core->mlx, core->bomb.t.ptr);
	move_player(core);
	return (0);
}

int	main(int argc, char **argv)
{
	t_core	*core;

	if (argc != 2)
		ft_quit("wrong number of argument\n", NULL);
	if (ft_extention_check(argv[1]) != 0)
		ft_quit("wrong file extention\n", NULL);
	init_data(&core);
	if (ft_parse_map(core, argv[1], 0) != 0)
		ft_quit("unable to retrieve map info\n", core);
	if (ft_map_validation(core) != 0)
		ft_quit("invalid map\n", core);
	core->mlx = mlx_init();
	if (core->mlx == NULL)
		return (1);
	core->win = mlx_new_window(core->mlx, S_W, S_H, "cub3d");
	if (core->win == NULL)
		return (free(core->mlx), 1);
	mlx_loop_hook(core->mlx, make_image, core);
	mlx_hook(core->win, 4, 1L << 2, mouse_on, core);
	mlx_hook(core->win, 5, 1L << 3, mouse_off, core);
	mlx_hook(core->win, 2, 1L << 0, close_win, core);
	mlx_hook(core->win, 3, 1L << 1, stop_flag, core);
	mlx_hook(core->win, 6, 1L << 6, mouse_move, core);
	mlx_hook(core->win, DestroyNotify, StructureNotifyMask, &on_destroy, core);
	mlx_loop(core->mlx);
}
