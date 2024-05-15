/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extention_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:22:55 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/15 12:51:16 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char    *get_dot(char *file)
{
    char    *dot;
    
    dot = ft_strchr(file, '.');
    if (dot == NULL || dot == file)
        return ("");
    dot++;
    return (dot);
}

int ft_extention_check(char *file)
{
    if (ft_strncmp(get_dot(file), "cub", 4) != 0)
        return (1);
    return (0);
}
