/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extention_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:22:55 by trysinsk          #+#    #+#             */
/*   Updated: 2024/06/06 13:45:21 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*get_dot(char *file)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (dot == NULL || dot == file)
		return ("");
	dot++;
	return (dot);
}

int	ft_extention_check(char *file)
{
	if (ft_strncmp(get_dot(file), "cub", 4) != 0)
		return (1);
	return (0);
}

void	ft_image_extention_check(t_core *core, char *file, char *ret)
{
	if (ft_strncmp(get_dot(ret), "xpm", 4) != 0)
	{
		ft_printf("Image file is not a .xpm file\n");
		free (file);
		free (ret);
		clean_data(core);
		exit(0);
	}
}

void	rgb_color_check(t_color *color)
{
	if (color->r < 0)
		color->r = 0;
	if (color->g < 0)
		color->g = 0;
	if (color->b < 0)
		color->b = 0;
	if (color->r > 255)
		color->r = 255;
	if (color->g > 255)
		color->g = 255;
	if (color->b > 255)
		color->b = 255;
}
