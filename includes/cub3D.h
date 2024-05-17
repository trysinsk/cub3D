/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:03:20 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/17 11:26:39 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "libft.h"


# define S_W 1900 // screen width
# define S_H 1000 // screen height
# define TILE_SIZE 30 // tile size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4 // player speed

# define W      122
# define A      113
# define S      115
# define D      100
# define UP     65362
# define DOWN   65364
# define LEFT   65361
# define RIGHT  65363

typedef struct s_player
{
    int player_x;   //position x pixels
    int player_y;   //position y pixels
    double angle;   //player angle
    float   fov_rd; //field of view in radians
    int rotation;   //rotation flag
    int left_right; //left or right flag
    int up_down;    //up or down flag
}   t_player;

typedef struct s_ray
{
    double ray_angle;
    double distance;
    int flag_wall;
}   t_ray;

typedef struct s_data
{
    char    **map;
    int     player_x;   //base x position on the map
    int     player_y;   //base y position on the map
    int     height;
    int     width;
    char    *no;        //path to textures below
    char    *so;
    char    *we;
    char    *ea;
    char    *f;
    char    *c;
}   t_data;

typedef struct s_core
{
    void        *mlx;
    void        *win;
    void        *img;
    t_player    *player;
    t_ray       *ray;
    t_data      *data;
}   t_core;

//     error and quiting
void    ft_quit(char *str);

//     map checking
int		ft_extention_check(char *file);
int     ft_parse_map(t_core *core, char *file, int index);
int     ft_retrieve_map(t_core *core, int fd, char *line);


#endif