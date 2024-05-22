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


// put pixel with color depending on fractol value
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

// fill the image file with the colored pixels based on the chosen fractol
void	fill_image(t_core vars)
{
	int		i;
	int		j;
	int		color;

	i = -1;
	while (i++ < S_W)
	{
		j = -1;
		while (j++ < S_H)
		{
			color = create_trgb(1, vars.data->f.R, vars.data->f.G, vars.data->f.B);
			img_pix_put(&vars, i, j, color);
		}
	}
}
// render the image into the window
int	render(t_core *vars)
{
	fill_image(*vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}
// destroy window and display and free data with closing window with mouse
int	on_destroy(t_core *data)
{
	ft_printf("in on destroy\n");
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
	ft_printf("in close win: %d\n", keycode);
	if (keycode == XK_Escape)
		on_destroy(core);
	return (0);
}
