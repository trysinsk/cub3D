/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:06:13 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/22 11:19:58 by trysinsk         ###   ########.fr       */
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

void    init_data(t_core **core)
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
    (*core)->data->height = -1;
    (*core)->data->width = -1;
    (*core)->data->player_x = -1;
    (*core)->data->player_y = -1;
    ft_printf("Allocation of memory complete.\n");
}

int main(int argc, char **argv)
{
    t_core *core;
    t_img   img;
    char    *relative_path = "tree.xpm";
    //int     img_width;
    //int     img_height;
    int		count_h;
	int		count_w;

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

    img.ptr = mlx_xpm_file_to_image(core->mlx, relative_path, &img.width, &img.height);
    img.data = (int *)mlx_get_data_addr(img.ptr, &img.bpp, &img.size_l, &img.endian);

	count_h = -1;
	while (++count_h < img.height)
	{
		count_w = -1;
		while (++count_w < img.width / 2)
		{
			if (count_w % 2)
				img.data[count_h * img.width + count_w] = 0xFFFFFF;
			else
				img.data[count_h * img.width + count_w] = 0xFF0000;
		}
	}
	mlx_put_image_to_window(core->mlx, core->win, img.ptr, 50, 50);

    //core->img = mlx_new_image(core->mlx, S_W, S_H);
    //core->addr = mlx_get_data_addr(core->img, &core->bpp,
	//		&core->line_len, &core->endian);

    //core->img = mlx_xpm_file_to_image(core->mlx, relative_path, &img_width, &img_height);
    //if (core->img == NULL)
    //    ft_printf("error\n");

    //mlx_put_image_to_window(core->mlx, core->win, core->img, 50, 50);

    mlx_hook(core->win, 2, 1L << 0, close_win, core);
	mlx_hook(core->win, DestroyNotify, StructureNotifyMask, &on_destroy, core);

	//mlx_loop_hook(core->mlx, render, core);


    //mlx_hook(core->win, DestroyNotify, StructureNotifyMask, &exit_hook, &core);
	//mlx_hook(core->win, KeyPress, KeyPressMask, &handle_keypress, &core);
	//mlx_hook(core->win, KeyPress, KeyReleaseMask, &handle_keyrelease, &core);
    mlx_loop(core->mlx);

    //if (core)
    //    clean_data(core);
    //return (0);
}