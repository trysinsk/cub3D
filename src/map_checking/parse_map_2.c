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

    i = 0;
    (core)->data->map = malloc ((30 + 1) * sizeof(char *));
    (core)->data->width = ft_strlen(line);
    while (line != NULL)
    {
        if (i >= 30)
            return (1);
        if ((core)->data->width < (int)ft_strlen(line))
            (core)->data->width = ft_strlen(line);
        (core)->data->map[i] = ft_strdup(line);
        if ((core)->data->map[i] == NULL)
            return (1);
        i++;
        free(line);
        line = ft_get_next_line(fd);
    }
    (core)->data->height = i;
    (core)->data->map[i] = "\0";
    i = 0;
    printf ("height: %d\n", (core->data->height));
    printf ("width: %d\n", (core->data->width));
    while ((core)->data->map[i] != NULL)
    {
        printf ("%s", (core->data->map[i]));
        i++;
    }
    return (0);
}