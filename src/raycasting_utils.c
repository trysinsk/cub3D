/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:17:04 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/23 14:40:12 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int in_wall(double x, double y, t_core *core)
{
    printf("%f %f\n", x, y);
    printf("%d, %d\n", (int)(floor(y) / TILE_SIZE), (int)(floor(x) / TILE_SIZE));
    if(ft_strncmp(&core->data->map[(int)(floor(y) / TILE_SIZE)][(int)(floor(x) / TILE_SIZE)], "1", 1) == 0)
        return (1);
    printf("here\n");
    return (0);
}

double horizontal_inter(t_core *core, double angle)
{
    double  ay;
    double  ax;
    double  dist;
    double  delta_x;
    double  delta_y;

    if (angle > 0 && angle < PI)
        ay = floor((core->player->player_y / TILE_SIZE)) * TILE_SIZE - 1;
    else
        ay = floor((core->player->player_y / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;

    ax = core->player->player_x + (core->player->player_y - ay) / tan(angle);
    if (ax < 0)
        return (S_H * TILE_SIZE * 100);

    if (in_wall(ax, ay, core) == 1)
    {
        delta_x = ax - core->player->player_x;
        delta_y = ay - core->player->player_y;
        dist = sqrt(delta_x * delta_x + delta_y * delta_y);
        return (dist);
    }
    delta_x = TILE_SIZE / tan(angle);
    if (angle > 0 && angle < PI)
        delta_y = -TILE_SIZE;
    else
        delta_y = TILE_SIZE;

    while (in_wall(ax, ay, core) != 1)
    {

        ax = ax + delta_x;
        ay = ay + delta_y;
    }
    delta_x = ax - core->player->player_x;
    delta_y = ay - core->player->player_y;
    dist = sqrt(delta_x * delta_x + delta_y * delta_y);
    return (floor(dist));
}

double vertical_inter(t_core *core, double angle)
{
    double  ay;
    double  ax;
    double  dist;
    double  delta_x;
    double  delta_y;

    if (angle > PI / 2 && angle < 3 * PI / 2)
        ax = floor((core->player->player_x / TILE_SIZE)) * TILE_SIZE - 1;
    else
        ax = floor((core->player->player_x / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;

    ay = core->player->player_y + (core->player->player_x - ax) * tan(angle);
    if (ay < 0)
        return (S_H * TILE_SIZE * 100);

    if (in_wall(ax, ay, core) == 1)
    {
        delta_x = ax - core->player->player_x;
        delta_y = ay - core->player->player_y;
        dist = sqrt(delta_x * delta_x + delta_y * delta_y);
        return (dist);
    }
    delta_y = TILE_SIZE * tan(angle);
    if (angle > PI / 2 && angle < 3 * PI / 2)
        delta_x = -TILE_SIZE;
    else
        delta_x = TILE_SIZE;

    while (in_wall(ax, ay, core) != 1)
    {

        ax = ax + delta_x;
        ay = ay + delta_y;
    }
    delta_x = ax - core->player->player_x;
    delta_y = ay - core->player->player_y;
    dist = sqrt(delta_x * delta_x + delta_y * delta_y);
    return (floor(dist));
}

int  height_of_wall(double dist)
{
    double  height;
    double  d_to_p;

    d_to_p = S_W / 2 / tan(FOV * PI / 180 / 2);
    height = d_to_p * TILE_SIZE / dist;
    //printf("distance to screen: %f, distance to wall: %f, height of wall: %d, height of screen: %d, hiehgt of projected wall: %f\n", d_to_p, dist, TILE_SIZE, S_H, height);
    return (floor(height));
}
void	insert_column(t_core *core, int x, int height)
{
	int		count_h;
	int		color;
    int     top;
	char	*relative_path = "tree.xpm";

	core->img2.ptr = mlx_xpm_file_to_image(core->mlx, relative_path,
		&(core->img2).width, &core->img2.height);
	core->img2.data = (int *)mlx_get_data_addr(core->img2.ptr,
		&core->img2.bpp, &core->img2.size_l, &core->img2.endian);

	color = core->img2.data[2];
	count_h = S_H / 2 - height / 2;
    top = S_H / 2 + height / 2;
    if (count_h < 0)
    {
        count_h = 0;
        top = S_H;
    }
	while (count_h < top)
	{
		img_pix_put(core, x, count_h, color);
        count_h++;
	}
}
void	raycast_loop(t_core *core)
{
    int     i;
    double  dist_v;
    double  dist;
    double  delta_r;
    int  height;
    double  angle;

    angle = core->player->angle - (FOV * PI / 180 / 2);
    delta_r = FOV * PI / 180 / S_W;

    i = 0;
    while (i < S_W)
    {
        dist_v = S_H * TILE_SIZE;
        //dist = horizontal_inter(core, angle);
        dist = vertical_inter(core, angle);
        //if (dist_v < dist)
        //    dist = dist_v;
        dist = dist * cos(angle - core->player->angle);
        height = height_of_wall(dist);
        insert_column(core, S_W - i, height);
        i++;
        angle += delta_r;
    }
}