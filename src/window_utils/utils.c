/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:17:16 by mevonuk           #+#    #+#             */
/*   Updated: 2024/05/22 11:26:07 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// destroy window and display and free data with closing window with mouse
int	on_destroy(t_core *data)
{
	if (!data)
		exit(0);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	clean_data(data);
	exit(0);
	return (0);
}

// close window and free memory with ESC key
int	close_win(int keycode, t_core *core)
{
	if (keycode == ESC)
		on_destroy(core);
	return (0);
}
