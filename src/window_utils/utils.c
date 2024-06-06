/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:17:16 by mevonuk           #+#    #+#             */
/*   Updated: 2024/06/03 08:53:22 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// put pixel with color depending on value
void	img_pix_put(t_core *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

// destroy window and display and free data with closing window with mouse
int	on_destroy(t_core *data)
{
	if (!data)
		exit(0);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	printf("You have exited the game.\n");
	clean_data(data);
	exit(0);
	return (0);
}

// close window and free memory with ESC key
int	key_control(int keycode, t_core *core)
{
	if (keycode == XK_Escape)
		on_destroy(core);
	if (keycode == 32)
		interact(core);
	if (keycode == W || keycode == 119 || keycode == 65362)
		core->player->up_down = 1;
	if (keycode == S || keycode == 65364)
		core->player->up_down = -1;
	if (keycode == D)
		core->player->left_right = -1;
	if (keycode == A || keycode == 97)
		core->player->left_right = 1;
	if (keycode == RIGHT)
		core->player->rotation = 1;
	if (keycode == LEFT)
		core->player->rotation = -1;
	if (keycode == MAP)
		core->map = (core->map + 1) % 2;
	return (0);
}

int	stop_flag(int keycode, t_core *core)
{
	if (keycode == W || keycode == 119 || keycode == 65362)
		core->player->up_down = 0;
	if (keycode == S || keycode == 65364)
		core->player->up_down = 0;
	if (keycode == D)
		core->player->left_right = 0;
	if (keycode == A || keycode == 97)
		core->player->left_right = 0;
	if (keycode == RIGHT)
		core->player->rotation = 0;
	if (keycode == LEFT)
		core->player->rotation = 0;
	return (0);
}
