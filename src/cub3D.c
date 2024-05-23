/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:06:13 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/23 12:40:27 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	exit_hook(t_core *core)
{
	mlx_destroy_window(core->mlx, core->win);
	mlx_destroy_display(core->mlx);
	free(core->mlx);
	return (0);
}

int	handle_keyrelease(int keysym, t_core *core)
{
    (void) core;
    ft_printf("%d\n", keysym);
    /*if (keysym == W)
	if (keysym == S)
	if (keysym == A)
	if (keysym == D)
    if (keysym == LEFT)
    if (keysym == RIGHT)*/
	return (0);
}

int	handle_keypress(int keysym, t_core *core)
{
	ft_printf("%d\n", keysym);
	if (keysym == XK_Escape)
		mlx_destroy_window(core->mlx, core->win);
    /*if (keysym == W)
	if (keysym == S)
	if (keysym == A)
	if (keysym == D)
    if (keysym == LEFT)
    if (keysym == RIGHT)*/
	return (0);
}

void	init_data(t_core **core)
{
	*core = (t_core *)malloc(1 * sizeof(t_core));
	if (!core)
		ft_quit("error: allocation failed\n");
	(*core)->data = (t_data *)malloc(1 *sizeof(t_data));
	if (!(*core)->data)
	{
		free(*core);
		ft_quit("error: allocation failed\n");
	}
	else
	{
		(*core)->data->map = NULL;
		(*core)->data->no = NULL;
		(*core)->data->so = NULL;
		(*core)->data->we = NULL;
		(*core)->data->ea = NULL;
	}
	(*core)->player = (t_player *)malloc(1 *sizeof(t_player));
	if (!(*core)->player)
	{
		free((*core)->data);
		free(*core);
		ft_quit("error: allocation failed\n");
	}
	(*core)->ray = (t_ray *)malloc(1 *sizeof(t_ray));
	if (!(*core)->ray)
	{
		free((*core)->data);
		free((*core)->player);
		free(*core);
		ft_quit("error: allocation failed\n");
	}
	(*core)->data->height = -1;
	(*core)->data->width = -1;
	(*core)->data->player_x = -1;
	(*core)->data->player_y = -1;
}

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
				color = create_trgb(1, core->data->f.r,
					core->data->f.g, core->data->f.b);
			else
				color = create_trgb(1, core->data->c.r,
					core->data->c.g, core->data->c.b);
			img_pix_put(core, count_w, count_h, color);
		}
	}
}

void	insert_column(t_core *core, int x, int y_start, int	length)
{
	int		count_h;
	//int		count_w;
	int		color;
	char	*relative_path = "tree.xpm";

	core->img2.ptr = mlx_xpm_file_to_image(core->mlx, relative_path,
		&(core->img2).width, &core->img2.height);
	core->img2.data = (int *)mlx_get_data_addr(core->img2.ptr,
		&core->img2.bpp, &core->img2.size_l, &core->img2.endian);

	// count_h = -1;
	// while (++count_h < core->img2.height)
	// {
	// 	count_w = -1;
	// 	while (++count_w < core->img2.width)
	// 	{
	// 		color = core->img2.data[count_h * core->img2.width + count_w];
	// 		img_pix_put(core, x + count_w, count_h, color);
	// 	}
	// }

	color = core->img2.data[2];
	count_h = y_start - 1;
	while (++count_h < y_start + length)
	{
		img_pix_put(core, x, count_h, color);
	}
}

int	make_image(t_core *core)
{
	core->img = mlx_new_image(core->mlx, S_W, S_H);
	core->addr = mlx_get_data_addr(core->img, &core->bpp,
			&core->line_len, &core->endian);
	cieling_floor(core);
	//insert_column(core, 60, 60, 20);
	raycast_loop(core);
	mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
	mlx_destroy_image(core->mlx, core->img);
	return (0);
}

int	main(int argc, char **argv)
{
	t_core	*core;

	if (argc != 2)
		ft_quit("wrong number of argument\n");
    //first checking of the map extention
	if (ft_extention_check(argv[1]) != 0)
		ft_quit("wrong file extention\n");
    //initialisation of data
	init_data(&core);
    //then retrieving of the map info and map structure
	if (ft_parse_map(core, argv[1], 0) != 0)
		ft_quit("unable to retrieve map info\n");
    //cheking of map conformity
	if (ft_map_validation(core) != 0)
		ft_quit("invalid map\n");
    //launch game
    //handle keys
	core->mlx = mlx_init();
	if (core->mlx == NULL)
		return (1);
	core->win = mlx_new_window(core->mlx, S_W, S_H, "cub3d");
	if (core->win == NULL)
		return (free(core->mlx), 1);
	mlx_loop_hook(core->mlx, make_image, core);
	mlx_hook(core->win, 2, 1L << 0, close_win, core);
	mlx_hook(core->win, DestroyNotify, StructureNotifyMask, &on_destroy, core);
	mlx_loop(core->mlx);
}
