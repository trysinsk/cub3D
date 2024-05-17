/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:53:29 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/15 13:38:46 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char    *get_color(char *line)
{
    char    *ret;
    char    *color;
    int     i;

    ret = malloc((ft_strlen(line) + 1) * sizeof(char));
    if (!ret)
        return (NULL);
    color = ft_strchr(line, ' ');
    if (color == NULL || color == line)
        return (NULL);
    i = 0;
    color++;
    while (*color != '\n' && *color != '\0')
    {
        ret[i] = *color;
        i++;
        color++;
    }
    ret[i] = '\0';
    return (ret);
}

char    *get_path(char *line)
{
    char    *ret;
    char    *path;
    int     i;

    ft_printf("in get_path\n");
    ret = malloc((ft_strlen(line) + 1) * sizeof(char));
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
    ft_printf("returning ret from get_path\n");
    return (ret);
}

void    fill_texture(t_core *core, char *line)
{
    ft_printf("in fill_texture\n");
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

    ft_printf("starting parse_map\n");
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (1);
    line = ft_get_next_line(fd);
    ft_printf("read line\n");
    if (line == NULL)
        return (1);
    while (line && line[0] != '1' && line [0] != ' ')
    {
        ft_printf("in while loop\n");
        if (check_texture(line))
        {
            ft_printf("checking texture\n");
            fill_texture(core, line);
            index++;
            ft_printf("texture checked\n");
        }
        free(line);
        ft_printf("freed line\n");
        line = ft_get_next_line(fd);
    }
    printf ("NO: %s\n", (core)->data->no);
    printf ("SO: %s\n", (core)->data->so);
    printf ("WE: %s\n", (core)->data->we);
    printf ("EA: %s\n", (core)->data->ea);
    printf ("f: %s\n", (core)->data->f);
    printf ("c: %s\n", (core)->data->c);
    return (0);

}