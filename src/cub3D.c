/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:06:13 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/15 12:42:01 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    init_data(t_core **core)
{
	*core = malloc(1 * sizeof(t_core));
    if (!core)
        ft_quit("error: allocation failed\n");
    (*core)->data = malloc(1 *sizeof(t_data));
    if (!(*core)->data)
    {
        free(*core);
        ft_quit("error: allocation failed\n");
    }
}

int main(int argc, char **argv)
{
    t_core *core;
    
    if (argc != 2)
        ft_quit("wrong number of argument\n");
    //first checking of the map extention
    if (ft_extention_check(argv[1]) != 0)
        ft_quit("wrong file extention\n");
    //initialisation of data
    init_data(&core);
    //then retrieving of the map info and map structure
    if (ft_parse_map(&core, argv[1], 0) != 0)
        ft_quit("unable to retrieve map info\n");
    //cheking of map conformity
    /*if (ft_check_map_integrity(core->data) != 0)
        ft_quit("map invalide\n");*/
    //launch game
    return (0);
}