/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:21:41 by mevonuk           #+#    #+#             */
/*   Updated: 2024/05/22 12:22:30 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// store RGB color in an integer
int	create_trgb(int t, int r, int g, int b)
{
	//ft_printf("creating color int from R: %d, G: %d, B: %d\n", r, g, b);
	return (t << 24 | r << 16 | g << 8 | b);
}
