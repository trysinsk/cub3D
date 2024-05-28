/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:03:20 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/28 14:32:09 by mevonuk          ###   ########.fr       */
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
# define ROTATION_SPEED 0.045	// rotation speed
# define PLAYER_SPEED 4			// player speed
# define PI 3.14159265

# define W		122
# define A		113
# define S		115
# define D		100
# define UP		65362
# define DOWN	65364
# define LEFT	65361
# define RIGHT	65363

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
}	t_player;

typedef struct s_ray
{
	double	ray_angle;
	double	distance;
	int		flag_wall;
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
	int		mapi[MAX_TILE][MAX_TILE];
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

typedef struct s_core
{
	void		*mlx;
	void		*win;
	void		*img;
	t_img		img_n;
	t_img		img_s;
	t_img		img_e;
	t_img		img_w;
	char		*addr;
	int			bpp;
	int			endian;
	int			line_len;
	t_player	*player;
	t_ray		*ray;
	t_data		*data;
}	t_core;

//     error and quiting
void	ft_quit(char *str);
void	clean_data(t_core *core);
void	ft_free_tab(char **array);

// window tools
int		on_destroy(t_core *data);
int		close_win(int keycode, t_core *core);
void	img_pix_put(t_core *img, int x, int y, int color);
void	fill_image(t_core vars);
void	img_pix_put(t_core *img, int x, int y, int color);
int		render(t_core *vars);
int		create_trgb(int t, int r, int g, int b);

//     map checking
int		ft_extention_check(char *file);
int		ft_parse_map(t_core *core, char *file, int index);
int		ft_retrieve_map(t_core *core, int fd, char *line);
int		ft_map_validation(t_core *core);
int		ft_check_outer_walls(t_core *core, char **map, int x, int y);
int		ft_check_spaces(t_core *core, char **map, int x, int y);

//		raycating

void	raycast_loop(t_core *core);

#endif
