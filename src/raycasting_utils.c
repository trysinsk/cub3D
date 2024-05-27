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

int hit_wall(float x, float y, t_core *core)
{
    int pos_x;
    int pos_y;

    if (x < 0 || y < 0)
        return (1);
    pos_x = floor (x / TILE_SIZE);
    pos_y = floor (y / TILE_SIZE);
    if (pos_y >= core->data->height || pos_x >= core->data->width)
        return (1);
    if (core->data->map[pos_y] && x <= (int)ft_strlen(core->data->map[pos_y]))
        {
            if (core->data->map[pos_y][pos_x] == '1')
                return (0);
        }
    return (1);
}

double get_y_wall(t_core *core)
{
    float   inter_x;
    float   inter_y;
    float   step_x;
    float   step_y;
    int     adjust;

    inter_y = floor((core->player->player_y / TILE_SIZE)) * TILE_SIZE;
    step_y = TILE_SIZE;
    inter_x = (core->player->player_x) + (inter_y - core->player->player_y) / tan(core->ray->ray_angle);
    step_x = TILE_SIZE / tan(core->ray->ray_angle);
    adjust = 1;
    if (core->ray->ray_angle > 0 && core->ray->ray_angle < PI)
    {
        inter_y += TILE_SIZE;
        adjust = -1;
    }
    else
        step_y *= -1;
    while (!hit_wall(inter_x, inter_y - adjust, core))
    {
        inter_y += step_y;
        inter_x += step_x;
    }
    return (sqrt(pow(inter_x - core->player->player_x, 2) + pow(inter_y - core->player->player_y, 2)));
}

double get_x_wall(t_core *core)
{
    float   inter_x;
    float   inter_y;
    float   step_x;
    float   step_y;
    int     adjust;

    inter_x = floor((core->player->player_x / TILE_SIZE)) * TILE_SIZE;
    printf("player x: %f, y: %f\n", core->player->player_x, core->player->player_y);
    step_x = TILE_SIZE;
    inter_y = (core->player->player_y) + (inter_x - core->player->player_x) / tan(core->ray->ray_angle);
    step_y = TILE_SIZE / tan(core->ray->ray_angle);
    printf("angle: %f, iy: %f, sy: %f\n", core->ray->ray_angle /PI * 180, inter_y, step_y);
    adjust = 1;
    if (core->ray->ray_angle > (PI / 2) && core->ray->ray_angle < (3 * PI / 2))
    {
        inter_x += TILE_SIZE;
        adjust = -1;
    }
    else
        step_y *= -1;
    while (!hit_wall(inter_x, inter_y - adjust, core))
    {
        inter_y += step_y;
        inter_x += step_x;
    }
    return (sqrt(pow(inter_x - core->player->player_x, 2) + pow(inter_y - core->player->player_y, 2)));
}

int in_wall(float x, float y, t_core *core)
{
    if(ft_strncmp(&core->data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)], "1", 1) == 0)
        return (1);
    return (0);
}

float horizontal_inter(t_core *core, double angle)
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
        return (__DBL_MAX__);

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
    return (dist);
}

float vertical_inter(t_core *core, double angle)
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
        return (__DBL_MAX__);

    if (in_wall(ax, ay, core) == 1)
    {
        delta_x = ax - core->player->player_x;
        delta_y = ay - core->player->player_y;
        dist = sqrt(delta_x * delta_x + delta_y * delta_y);
        return (dist);
    }
    delta_y = TILE_SIZE / tan(angle);
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
    return (dist);
}

int  height_of_wall(t_core *core, double dist)
{
    double  height;
    double  d_to_p;

    d_to_p = S_W / 2 / tan(core->player->an_rad / 2);
    height = d_to_p * TILE_SIZE / dist;
    printf("distance to screen: %f, distance to wall: %f, height of wall: %d, height of screen: %d, hiehgt of projected wall: %f\n", d_to_p, dist, TILE_SIZE, S_H, height);
    return (floor(height));
}
void	insert_column(t_core *core, int x, int height)
{
	int		count_h;
	int		color;
	char	*relative_path = "tree.xpm";

	core->img2.ptr = mlx_xpm_file_to_image(core->mlx, relative_path,
		&(core->img2).width, &core->img2.height);
	core->img2.data = (int *)mlx_get_data_addr(core->img2.ptr,
		&core->img2.bpp, &core->img2.size_l, &core->img2.endian);

	color = core->img2.data[2];
	count_h = S_H / 2 - height / 2 - 1;
    if (count_h < 0)
    {
        count_h = 0;
    }
	while ((count_h < S_H / 2 + height / 2) && (count_h < S_H))
	{
		img_pix_put(core, x, count_h, color);
        count_h++;
	}
}
void	raycast_loop(t_core *core)
{
    int     i;
    double  dist_h;
    double  dist_v;
    double  dist;
    double  delta_r;
    int  height;

    core->ray->ray_angle = core->player->angle - (core->player->an_rad / 2);
    delta_r = core->player->an_rad / S_W;

    i = 0;
    while (i < S_W)
    {
        dist_h = __DBL_MAX__;
        dist_v = __DBL_MAX__;
        if (core->ray->ray_angle != 0 || core->ray->ray_angle != PI)
            dist_h = horizontal_inter(core, core->ray->ray_angle);
        printf("for %d, ver_distance is: %f\n", i, dist_h);
        if (core->ray->ray_angle != (PI / 2) || core->ray->ray_angle != (3 * PI / 2))
            dist_v = vertical_inter(core, core->ray->ray_angle);
        printf("for %f, hor_distance is: %f\n", core->ray->ray_angle / PI * 180, dist_v);
        dist = dist_h;
        if (dist_v < dist)
            dist = dist_v;
        dist = dist * cos(core->ray->ray_angle - core->player->angle);
        printf("corrected distance is: %f\n", dist);
        height = height_of_wall(core, dist);
        printf("height of wall is: %d of %d\n", height, S_H);
        insert_column(core, S_W - i, height);
        i++;
        core->ray->ray_angle += delta_r;
    }
}