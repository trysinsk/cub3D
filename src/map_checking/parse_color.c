/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:59:34 by mevonuk           #+#    #+#             */
/*   Updated: 2024/06/10 10:21:26 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	split_check(int i, char **ctab)
{
	while (i < 2)
	{
		if (ctab[i] == NULL)
		{
			printf("error: bad value for color, using default\n");
			return (1);
		}
		i++;
	}
	return (0);
}

t_color	get_color(char *line)
{
	t_color	ret;
	char	*color;
	char	**ctab;

	ret.r = 0;
	ret.g = 0;
	ret.b = 0;
	color = ft_strchr(line, ' ');
	if (color == NULL || color == line)
		return (ret);
	color++;
	ctab = ft_split(color, ',');
	if (split_check(0, ctab) == 1)
	{
		ft_free_tab(ctab);
		return (ret);
	}
	ret.r = ft_atoi_color(ctab[0]);
	ret.g = ft_atoi_color(ctab[1]);
	ret.b = ft_atoi_color(ctab[2]);
	ft_free_tab(ctab);
	rgb_color_check(&ret);
	return (ret);
}
