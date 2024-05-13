/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:06:13 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/07 12:48:48 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    ft_quit(char *str)
{
    printf("%s", str);
    exit (1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        ft_quit("wrong number of argument\n");
    //first checking of the map extention and such
    if (!ft_extention_check(argv[1]))
        ft_quit("wrong file extention\n");
    //initialisation of data
    //then retrieving of the map
/*    if (!ft_parse_map(&core))
        ft_quit("unable to retrieve map\n");*/
    //cheking of map conformity
    //launch game
    return (0);
}