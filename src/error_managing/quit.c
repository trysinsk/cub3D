/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:37:04 by trysinsk          #+#    #+#             */
/*   Updated: 2024/06/03 11:03:12 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_quit(char *str, t_core *core)
{
	printf("Error: ");
	printf("%s", str);
	clean_data(core);
	exit (1);
}
