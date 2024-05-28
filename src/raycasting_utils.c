/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:17:04 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/28 12:39:33 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int in_wall(double x, double y, t_core *core)
{
    int i;
    int j;

    i = floor(x / TILE_SIZE);
    j = floor(y / TILE_SIZE);
    if(core->data->mapi[i][j] == 1)
    {
        //printf("%f %f\n", x, y);
        printf("wall at: %d, %d\n", i, j);
        return (1);
    }
    return (0);
}

double  distance(double x, double y)
{
    return (sqrt(x * x + y * y));
}

int in_bounds(double x, double y, t_core *core)
{
    if (x < 0 || x > (core->data->width - 1) * TILE_SIZE)
        return (1);
    if (y < 0 || y > core->data->height * TILE_SIZE)
        return (1);
    return (0);
}

double horizontal_inter(t_core *core, double angle)
{
    double  ay;
    double  ax;
    double  delta_x;
    double  delta_y;
    int     x_dir;
    int     y_dir;

    x_dir = 1;
    y_dir = 1;
    if (angle > 0 && angle < PI)
        y_dir = -1;
    if (angle > PI / 2 && angle < 3 * PI / 2)
        x_dir = -1;
    if (angle > 0 && angle < PI)
        ay = floor((core->player->player_y / TILE_SIZE)) * TILE_SIZE - .0001;
    else
        ay = floor((core->player->player_y / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
    ax = core->player->player_x + x_dir * fabs((core->player->player_y - ay) / tan(angle));
    delta_x = x_dir * fabs(TILE_SIZE / tan(angle));
    delta_y = y_dir * TILE_SIZE;
    printf("in horizontal:\nax: %f ay: %f\ndelta_x: %f delta_y: %f\n", ax, ay, delta_x, delta_y);
    printf("slope %f\n", delta_y/delta_x);
    while (in_bounds(ax, ay, core) == 0 && in_wall(ax, ay, core) != 1)
    {
        ax = ax + delta_x;
        ay = ay + delta_y;
    }
    return (distance(ax - core->player->player_x, ay - core->player->player_y));
}

double vertical_inter(t_core *core, double angle)
{
    double  ay;
    double  ax;
    double  delta_x;
    double  delta_y;
    int     x_dir;
    int     y_dir;

    x_dir = 1;
    y_dir = 1;
    if (angle > 0 && angle < PI)
        y_dir = -1;
    if (angle > PI / 2 && angle < 3 * PI / 2)
        x_dir = -1;
    if (angle > PI / 2 && angle < 3 * PI / 2)
        ax = floor((core->player->player_x / TILE_SIZE)) * TILE_SIZE - .0001;
    else
        ax = floor((core->player->player_x / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
    ay = core->player->player_y + y_dir * fabs((core->player->player_x - ax) * tan(angle));
    delta_y = y_dir * fabs(TILE_SIZE * tan(angle));
    delta_x = x_dir * TILE_SIZE;
    printf("in vertical:\nax: %f ay: %f\ndelta_x: %f delta_y: %f\n", ax, ay, delta_x, delta_y);
    printf("slope %f\n", delta_y/delta_x);
    while (in_bounds(ax, ay, core) == 0 && in_wall(ax, ay, core) != 1)
    {
        ax = ax + delta_x;
        ay = ay + delta_y;
    }
    return (distance(ax - core->player->player_x, ay - core->player->player_y));
}

int  height_of_wall(double dist)
{
    double  height;
    double  d_to_p;

    d_to_p = S_W / 2 / tan(FOV * PI / 180 / 2);
    height = d_to_p * TILE_SIZE / dist;
    //printf("distance to screen: %f, distance to wall: %f, height of wall: %d, height of screen: %d, hiehgt of projected wall: %f\n", d_to_p, dist, TILE_SIZE, S_H, height);
    return ((int)(height));
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

    i = 1;
    while (i <= S_W)
    {
        dist = S_H * TILE_SIZE;
        dist_v = dist;
        printf("-------i:%d angle: %f--------\n", i, angle / PI * 180);
        //if (!(angle / PI * 180 > 172 && angle / PI * 180 < 188))
        dist = horizontal_inter(core, angle);
        printf ("horizontal distance: %f\n", dist);
        //if (!(angle / PI * 180 > 88 && angle / PI * 180 < 92) && !(angle / PI * 180 > 268 && angle / PI * 180 < 272))
        dist_v = vertical_inter(core, angle);
        printf ("vertical distance: %f\n", dist_v);
        if (dist_v < dist)
            dist = dist_v;
        printf ("minimum distance: %f\n", dist);
        dist = dist * cos(angle - core->player->angle);
        printf ("corrected distance: %f\n\n", dist);
        height = height_of_wall(dist);
        printf("height of wall: %d\n\n", height);
        insert_column(core, S_W - i, height);
        i++;
        angle += delta_r;
    }
}