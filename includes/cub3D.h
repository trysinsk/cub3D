/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:03:20 by trysinsk          #+#    #+#             */
/*   Updated: 2024/06/04 13:24:32 by trysinsk         ###   ########.fr       */
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

# define S_W 620				// screen width
# define S_H 400				// screen height
# define MAX_TILE 100			// maximum size of map
# define TILE_SIZE 64			// tile size
# define FOV 60					// field of view
# define ROTATION_SPEED 0.02	// rotation speed
# define PLAYER_SPEED 2			// player speed
# define PI 3.14159265
# define WALL_BUFFER 10
# define ILLUSION_BUFFER 40

# define W		122
# define A		113
# define S		115
# define D		100
# define UP		65362
# define DOWN	65364
# define LEFT	65361
# define RIGHT	65363
# define MAP	109

# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define MOUSE_WHEEL_BTN 2
# define MOUSE_BTN_L 1
# define MOUSE_BTN_R 3

typedef struct s_img
{
	void	*ptr;
	int		*data;
	int		width;
	int		height;
	int		size_l;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	player_x;
	double	player_y;
	double	angle;
	double	an_rad;
	double	fov_rd;
	int		rotation;
	int		left_right;
	int		up_down;
	int		mouse_x;
	int		bomb_count;
}	t_player;

typedef struct s_ray
{
	double	angle;
	int		x_dir;
	int		y_dir;
	int		flag;
	int		door;
	int		ax;
	int		ay;
	int		pxh;
	int		pyh;
	int		pxv;
	int		pyv;
}	t_ray;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_data
{
	char	**map;
	int		player_x;
	int		player_y;
	int		height;
	int		width;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	f;
	t_color	c;
}	t_data;

typedef struct s_sprite
{
	double	zbuf[S_W];
	double	x;
	double	y;
	t_img	img;
	double	planex;
	double	planey;
	double	dirx;
	double	diry;
} t_sprite;

typedef struct s_core
{
	void		*mlx;
	void		*win;
	void		*img;
	t_img		img_n;
	t_img		img_s;
	t_img		img_e;
	t_img		img_w;
	t_img		img_door;
	char		*addr;
	int			bpp;
	int			endian;
	int			line_len;
	int			map;
	t_player	*player;
	t_ray		*ray;
	t_data		*data;
	t_sprite	bomb;
}	t_core;

void	init_data(t_core **core);

//     error and quiting
void	ft_quit(char *str, t_core *core);
void	clean_data(t_core *core);
void	ft_free_tab(char **array);

// window tools
int		on_destroy(t_core *data);
int		close_win(int keycode, t_core *core);
void	img_pix_put(t_core *img, int x, int y, int color);
void	fill_image(t_core vars);
void	img_pix_put(t_core *img, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
int		mouse_on(int button, int x, int y, t_core *core);
int		mouse_off(int button, int x, int y, t_core *core);
int		mouse_move(int x, int y, t_core *core);

//     map checking
int		ft_extention_check(char *file);
int		ft_parse_map(t_core *core, char *file, int index);
int		ft_retrieve_map(t_core *core, int fd, char *line);
int		ft_map_validation(t_core *core);
int		ft_check_outer_walls(t_core *core, char **map, int x, int y);
int		ft_check_spaces(t_core *core, char **map, int x, int y);
int		check_texture_file(t_core *core);
void	ft_image_extention_check(t_core *core, char *file, char *ret);
void	rgb_color_check(t_core *core, char *line, t_color color);

//		raycasting
void	raycast_loop(t_core *core);
double	normalize_angle(double angle);
void	insert_column(t_core *core, int x, int height, double angle);
void	set_ray_direction(t_core *core, double angle);
int		in_bounds(double x, double y, t_core *core);
double	distance(double x, double y);
int		in_wall(double x, double y, t_core *core);
int		height_of_wall(double dist);

//2D map
void	toggle_map(t_core *core);

//		moves
int		stop_flag(int keycode, t_core *core);
void	interact(t_core *core);
void	move_player(t_core *core);
void	move_up(t_core *core);
void	move_down(t_core *core);
void	move_right(t_core *core);
void	move_left(t_core *core);
void	rotate_left(t_core *core);
void	rotate_right(t_core *core);
int		is_in_wall(t_core *core, double pos, char c, char **map);

#endif
