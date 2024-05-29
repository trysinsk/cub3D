/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:25:03 by mevonuk           #+#    #+#             */
/*   Updated: 2024/05/28 16:14:02 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_data(t_core *core)
{
	if (core)
	{
		if (core->data)
		{
			if (core->data->ea)
				free (core->data->ea);
			if (core->data->we)
				free (core->data->we);
			if (core->data->so)
				free (core->data->so);
			if (core->data->no)
				free (core->data->no);
			if (core->data->map)
				ft_free_tab(core->data->map);
			free (core->data);
		}
		if (core->player)
			free (core->player);
		if (core->ray)
			free (core->ray);
		free (core);
	}
}

void	print_table(char **tab)
{
	int	i;

	i = -1;
	if (tab == NULL)
		return ;
	while (tab[++i] != NULL)
		ft_printf("%s\n", tab[i]);
}

void	ft_free_tab(char **array)
{
	int	i;

	i = -1;
	if (array == NULL)
		return ;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
}
