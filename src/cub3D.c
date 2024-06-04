/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:06:13 by trysinsk          #+#    #+#             */
/*   Updated: 2024/06/04 13:35:10 by trysinsk         ###   ########.fr       */
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

int	find_sprite(t_core *core)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < core->data->width - 1)
	{
		j = 0;
		while (j < core->data->height)
		{
			if (core->data->map[j][i] == 'B')
			{
				core->bomb.x = i * TILE_SIZE + TILE_SIZE / 2;
				core->bomb.y = j * TILE_SIZE + TILE_SIZE / 2;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	draw_sprite(t_core *core)
{
	double	sx;
	double	sy;
	int		spritesx;
	int		spriteh;
	int		xs;
	int		ys;
	int		xe;
	int		ye;
	int		i;
	int		j;
	int		color;
	int		counter;
	double	d_to_p;
	double	angbomb;
	double	ds;
	double	deltax;
	double	deltay;
	double	planex;
	double	planey;
	double	invDet;
	double	tx;
	double	ty;

	d_to_p = S_W / 2 / tan(FOV * PI / 180 / 2);
	sx = core->bomb.x - core->player->player_x;
	sy = core->bomb.y - core->player->player_y;
	
	deltax = cos(core->player->angle);
	deltay = -sin(core->player->angle);
	printf("player angle: %f deltax: %f deltay: %f dis: %f\n", core->player->angle *180/PI, deltax, deltay, deltax*deltax + deltay*deltay);

	planex = deltax * cos(PI / 2) - deltay * sin(PI / 2);
	planey = deltax * sin(PI / 2) + deltay * cos(PI / 2);
	printf("planex: %f planey: %f dis: %f\n", planex, planey, planex*planex + planey*planey);

	invDet = 1.0 / (planex * deltay - deltax * planey);
	printf("invDet: %f\n", invDet);

	tx = invDet * (deltay * sx - deltay * sy);
	ty = invDet * (-planey * sx + planex * sy);
	printf("tx %f ty %f\n", tx, ty);

	ds = distance(sx, sy);
	printf("bomb at %f, %f with respect to player\n", sx, sy);
	angbomb = fabs(core->player->angle - atan((double)-sy/(double)sx)) * 180 / PI;
	if (angbomb > 180)
		angbomb = angbomb - 360;
	printf("angle to bomb with respect to player view= %f\n", angbomb);
	if (fabs(angbomb) < 45)
	{

		spritesx = (int)(S_W / 2 * (1.0 + tx / ty)); //S_W / 2 - ds * sin(angbomb * PI / 180);
		printf("1-tx/ty: %f\n", 1.0 + tx / ty);

		spriteh = abs((int)(S_H * TILE_SIZE / ty)); //TILE_SIZE / distance(sx, sy) * d_to_p;
		printf("S_W: %d, ssx: %d, sh %d\n", S_W, spritesx, spriteh);

		spriteh = spriteh * cos(angbomb * PI / 180);

		ys = -spriteh / 2 + S_H / 2;
		if (ys < 0)
			ys = 0;
		ye = spriteh / 2 + S_H / 2;
		if (ye > S_H)
			ye = S_H;
		xs = -spriteh / 2 + spritesx;
		if (xs < 0)
			xs = 0;
		xe = spriteh / 2 + spritesx;
		if (xe > S_W)
			xe = S_W;
		i = xs;
		printf("i: %d %d, j: %d %d\n", xs, xe, ys, ye);
		while (i < xe)
		{
			if (distance(sx, sy) < core->bomb.zbuf[i])
			{
				j = ys;
				while (j < ye)
				{
					counter = (j * core->bomb.img.size_l
						+ (int) sx % TILE_SIZE * (core->bomb.img.bpp / 8)) / 4;
					counter = 1;
					color = core->bomb.img.data[counter];
					img_pix_put(core, i, j, color);
					j++;
				}
			}
			i++;
		}
	}
}

void	sprites(t_core *core)
{
	core->bomb.img.ptr = mlx_xpm_file_to_image(core->mlx,
			"./src/textures/bomb.xpm", &(core->bomb.img).width,
			&core->bomb.img.height);
	core->bomb.img.data = (int *)mlx_get_data_addr(core->bomb.img.ptr,
			&core->bomb.img.bpp, &core->bomb.img.size_l,
			&core->bomb.img.endian);
	if (find_sprite(core) == 1)
		draw_sprite(core);
}

int	make_image(t_core *core)
{
	core->img = mlx_new_image(core->mlx, S_W, S_H);
	core->addr = mlx_get_data_addr(core->img, &core->bpp,
			&core->line_len, &core->endian);
	init_textures(core);
	cieling_floor(core);
	raycast_loop(core);
	sprites(core);
	if (core->map == 1)
		toggle_map(core);
	mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
	mlx_destroy_image(core->mlx, core->img);
	mlx_destroy_image(core->mlx, core->img_n.ptr);
	mlx_destroy_image(core->mlx, core->img_s.ptr);
	mlx_destroy_image(core->mlx, core->img_e.ptr);
	mlx_destroy_image(core->mlx, core->img_w.ptr);
	mlx_destroy_image(core->mlx, core->img_door.ptr);
	mlx_destroy_image(core->mlx, core->bomb.img.ptr);
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
