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
    mlx_hook(core->win, DestroyNotify, StructureNotifyMask, &exit_hook, &core);
	mlx_hook(core->win, KeyPress, KeyPressMask, &handle_keypress, &core);
	mlx_hook(core->win, KeyPress, KeyReleaseMask, &handle_keyrelease, &core);
	mlx_loop(core->mlx);
    if (core)
        clean_data(core);
    return (0);
}