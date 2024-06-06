/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:17:12 by mevonuk           #+#    #+#             */
/*   Updated: 2024/06/06 14:17:30 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_ij(t_core *core, char c)
{
	if (c == 'i')
	{
		if (core->ray->flag == 0)
			return (floor(core->ray->pxh / TILE_SIZE));
		else
			return (floor(core->ray->pxv / TILE_SIZE));
	}
	else if (c == 'j')
	{
		if (core->ray->flag == 0)
			return (floor(core->ray->pyh / TILE_SIZE));
		else
			return (floor(core->ray->pyv / TILE_SIZE));
	}
	return (0);
}

int	in_special(t_core *core)
{
	int	i;
	int	j;

	i = get_ij(core, 'i');
	j = get_ij(core, 'j');
	if (core->data->map[j][i] == '2')
		return (1);
	if (core->data->map[j][i] == 'B')
		return (2);
	if (core->data->map[j][i] == 'X')
		return (3);
	if (core->data->map[j][i] == '4')
		return (4);
	if (core->data->map[j][i] == 'T')
		return (5);
	if (core->data->map[j][i] == 'h')
		return (6);
	if (core->data->map[j][i] == 'H')
		return (7);
	return (0);
}

int	get_special_texture(t_core *core, int counter)
{
	if (in_special(core) == 1)
		return (core->img_door.data[counter]);
	if (in_special(core) == 2)
		return (core->bomb.full.data[counter]);
	if (in_special(core) == 3)
		return (core->bomb.empty.data[counter]);
	if (in_special(core) == 4)
		return (core->bomb.wall.data[counter]);
	if (in_special(core) == 5)
		return (core->bomb.t.data[counter]);
	if (in_special(core) == 6 || in_special(core) == 7)
		return (core->bomb.hole.data[counter]);
	return (core->bomb.t.data[counter]);
}
