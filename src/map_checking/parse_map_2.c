/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:17:41 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/28 16:20:02 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(t_core *core)
{
	int	i;

	i = 0;
	printf("Map dimensions: %d by %d\n",
		core->data->width - 1, core->data->height);
	while ((core)->data->map[i] != NULL)
	{
		ft_printf("%s", (core->data->map[i]));
		i++;
	}
	ft_printf("\n");
}

int	allocate_map(t_core *core)
{
	int	i;

	core->data->map = (char **)malloc((MAX_TILE + 1) * sizeof(char *));
	if (core->data->map == NULL)
		return (1);
	i = 0;
	while (i < MAX_TILE)
	{
		core->data->map[i] = NULL;
		i++;
	}
	return (0);
}

int	size_check(char *line, int i)
{
	if ((int)ft_strlen(line) > MAX_TILE || i >= MAX_TILE)
	{
		free (line);
		return (1);
	}
	return (0);
}

int	ft_retrieve_map(t_core *core, int fd, char *line)
{
	int	i;

	if (allocate_map(core) == 1)
		return (1);
	i = 0;
	core->data->width = (int)ft_strlen(line);
	while (line != NULL)
	{
		if (size_check(line, i))
			return (1);
		if (core->data->width < (int)ft_strlen(line))
			core->data->width = (int)ft_strlen(line);
		core->data->map[i] = ft_strdup(line);
		if (core->data->map[i] == NULL)
		{
			ft_free_tab(core->data->map);
			return (1);
		}
		i++;
		free(line);
		line = ft_get_next_line(fd);
	}
	core->data->height = i;
	print_map(core);
	return (0);
}
