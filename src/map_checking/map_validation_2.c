/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:12:51 by trysinsk          #+#    #+#             */
/*   Updated: 2024/06/05 11:57:12 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_texture_file(t_core *core)
{
	int	fd;

	fd = open(core->data->no, O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	fd = open(core->data->so, O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	fd = open(core->data->ea, O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	fd = open(core->data->we, O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	return (0);
}

int	check_special_texture(void)
{
	int	fd;

	fd = open("./src/textures/bomb_full.xpm", O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	fd = open("./src/textures/bomb_empty.xpm", O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	fd = open("./src/textures/crumbling_peace.xpm", O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	fd = open("./src/textures/exit.xpm", O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	fd = open("./src/textures/door_closed.xpm", O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	return (0);
}

int	ft_check_surroundings(t_core *core, char **map, int x, int y)
{
	if (map[y][x + 1] != ' ' && map[y][x + 1] != '1'
		&& map[y][x + 1] != '\0' && map[y][x + 1] != '\n')
		return (1);
	if (x > 0 && (map[y][x - 1] != ' ' && map[y][x - 1] != '1'
		&& map[y][x - 1] != '\0' && map[y][x - 1] != '\n'))
		return (1);
	if (y > 0 && x <= (int)ft_strlen (map[y - 1])
		&& (map[y - 1][x] != ' ' && map[y - 1][x] != '1'
		&& map[y - 1][x] != '\0' && map[y - 1][x] != '\n'))
		return (1);
	if (y < (core->data->height -1) && x <= (int)ft_strlen (map[y + 1])
		&& (map[y + 1][x] != ' ' && map[y + 1][x] != '1'
		&& map[y + 1][x] != '\0' && map[y + 1][x] != '\n'))
		return (1);
	return (0);
}

int	ft_check_spaces(t_core *core, char **map, int x, int y)
{
	while (y < core->data->height)
	{
		x = 0;
		while (map[y][x] != '\n' && map[y][x] != '\0')
		{
			if (map[y][x] == ' ')
			{
				if (ft_check_surroundings(core, map, x, y) != 0)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_check_outer_walls(t_core *core, char **map, int x, int y)
{
	while (y < core->data->height)
	{
		if ((map[y][0] != '1' && map[y][0] != ' ')
			|| (map[y][(int)ft_strlen(map[y]) - 2] != '1'
			&& map[y][(int)ft_strlen(map[y]) - 2] != ' '))
			return (1);
		y++;
	}
	while (map[0][x] != '\0' && map[0][x] != '\n')
	{
		if (map[0][x] != '1' && map[0][x] != ' ')
			return (1);
		x++;
	}
	x = 0;
	while (map[core->data->height - 1][x] != '\0'
		&& map[core->data->height - 1][x] != '\n')
	{
		if (map[core->data->height - 1][x] != '1'
			&& map[core->data->height - 1][x] != ' ')
			return (1);
		x++;
	}
	return (0);
}
