/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:53:29 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/17 11:27:08 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_color    get_color(char *line)
{
    t_color    ret;
    char    *color;
    char    **ctab;

    ret.R = 0;
    ret.G = 0;
    ret.B = 0;
    color = ft_strchr(line, ' ');
    if (color == NULL || color == line)
        return (ret);
    color++;
    ctab = ft_split(color, ',');
    ret.R = ft_atoi(ctab[0]);
    ret.G = ft_atoi(ctab[1]);
    ret.B = ft_atoi(ctab[2]);
    ft_free_tab(ctab);
    return (ret);
}

char    *get_path(char *line)
{
    char    *ret;
    char    *path;
    int     i;

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
    return (ret);
}

void    fill_texture(t_core *core, char *line)
{
    if (!ft_strncmp(line, "NO", 2))
        (core)->data->no = get_path(line);
    else if (!ft_strncmp(line, "SO", 2))
        (core)->data->so = get_path(line);
    else if (!ft_strncmp(line, "WE", 2))
        (core)->data->we = get_path(line);
    else if (!ft_strncmp(line, "EA", 2))
        (core)->data->ea = get_path(line);
    else if (!ft_strncmp(line, "F", 1))
        (core)->data->f = get_color(line);
    else if (!ft_strncmp(line, "C", 1))
        (core)->data->c = get_color(line);
}

int check_texture(char *line)
{
    while ((*line == ' ' || (*line >=9 && *line <= 13)))
        line++;
    if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
        || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
        || (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)))
        return (1);
    return (0);
}

int ft_parse_map(t_core *core, char *file, int index)
{
    int fd;
    char *line;

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
    ft_printf("NO: %s\n", (core)->data->no);
    ft_printf("SO: %s\n", (core)->data->so);
    ft_printf("WE: %s\n", (core)->data->we);
    ft_printf("EA: %s\n", (core)->data->ea);
    ft_printf("f: %d %d %d\n", core->data->f.R, core->data->f.G, core->data->f.B);
    ft_printf("c: %d %d %d\n", core->data->c.R, core->data->c.G, core->data->c.B);
    if (ft_retrieve_map(core, fd, line) != 0)
        return (1);
    //free (line);
    return (0);

}