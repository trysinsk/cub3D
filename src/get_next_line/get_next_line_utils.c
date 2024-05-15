/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:35:02 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/15 11:34:02 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_lus;
	int		i;
	int		j;
	int		size;

	size = (ft_strlen(s1) + ft_strlen(s2));
	new_lus = malloc((size + 1) * sizeof(char));
	if (!new_lus || !s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new_lus[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new_lus[i + j] = s2[j];
		j++;
	}
	new_lus[size] = '\0';
	return (new_lus);
}

int	ft_find_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strlcpy(char *dst, char *src, int j)
{
	int	i;

	i = 0;
	while (src[j] != 0)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}
