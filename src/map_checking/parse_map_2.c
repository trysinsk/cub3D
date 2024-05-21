/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:17:41 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/17 11:24:46 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int     ft_retrieve_map(t_core *core, int fd, char *line)
{
    int     i;

    core->data->map = (char **)malloc((TILE_SIZE + 1) * sizeof(char *));
    if (core->data->map == NULL)
        return (1);
    i = 0;
    while (i < TILE_SIZE)
    {
        core->data->map[i] = NULL;
        i++;
    }
    i = 0;
    if (line)
        core->data->width = (int)ft_strlen(line);
    while (line != NULL)
    {
        if (i >= TILE_SIZE)
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
    ft_printf("exited while loop\n");
    core->data->height = i;
    ft_printf("height: %d\n", (core->data->height));
    i = 0;
    ft_printf("width: %d\n", (core->data->width));
    while ((core)->data->map[i] != NULL)
    {
        ft_printf("%s", (core->data->map[i]));
        i++;
    }
    ft_printf("\n");
    return (0);
}