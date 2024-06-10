/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:53:29 by trysinsk          #+#    #+#             */
/*   Updated: 2024/06/10 09:30:14 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_color	get_color(t_core *core, char *line)
{
	t_color	ret;
	char	*color;
	char	**ctab;
	int		i;

	i = 0;
	ret.r = 0;
	ret.g = 0;
	ret.b = 0;
	color = ft_strchr(line, ' ');
	if (color == NULL || color == line)
		return (ret);
	color++;
	ctab = ft_split(color, ',');
	while (i < 2)
	{
		if (ctab[i] == NULL)
			printf("error\n");
		i++;
	}
	ret.r = ft_atoi_color(ctab[0]);
	ret.g = ft_atoi_color(ctab[1]);
	ret.b = ft_atoi_color(ctab[2]);
	ft_free_tab(ctab);
	rgb_color_check(core, line, ret);
	printf("Note that non-numeric color choices are set to zero.\n");
	return (ret);
}

char	*get_path(t_core *core, char *line)
{
	char	*ret;
	char	*path;
	int		i;

	ret = (char *)malloc((ft_strlen(line) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	path = ft_strchr(line, '.');
	if (path == NULL || path == line)
		return (NULL);
	i = 0;
	while (*path != '\n' && *path != '\0')
	{
		ret[i] = *path;
		i++;
		path++;
	}
	ret[i] = '\0';
	ft_image_extention_check(core, line, ret);
	return (ret);
}

void	fill_texture(t_core *core, char *line)
{
	if (!ft_strncmp(line, "NO", 2) && core->data->no == NULL)
		core->data->no = get_path(core, line);
	else if (!ft_strncmp(line, "SO", 2) && core->data->so == NULL)
		core->data->so = get_path(core, line);
	else if (!ft_strncmp(line, "WE", 2) && core->data->we == NULL)
		core->data->we = get_path(core, line);
	else if (!ft_strncmp(line, "EA", 2) && core->data->ea == NULL)
		core->data->ea = get_path(core, line);
	else if (!ft_strncmp(line, "F", 1))
		core->data->f = get_color(core, line);
	else if (!ft_strncmp(line, "C", 1))
		core->data->c = get_color(core, line);
}

int	check_texture(char *line)
{
	while ((*line == ' ' || (*line >= 9 && *line <= 13)))
		line++;
	if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		|| (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)))
		return (1);
	return (0);
}

int	ft_parse_map(t_core *core, char *file, int index)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	line = ft_get_next_line(fd);
	if (line == NULL)
		return (1);
	while (line && line[0] != '1' && line [0] != ' ')
	{
		if (check_texture(line))
		{
			fill_texture(core, line);
			index++;
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	if (ft_retrieve_map(core, fd, line) != 0)
		return (1);
	close (fd);
	if (check_texture_file(core) == 1)
		return (1);
	return (0);
}
