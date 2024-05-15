/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:18:37 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/15 10:23:43 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0')
		&& (i < n))
	{
		if ((unsigned char)s1[i] > ((unsigned char)s2[i]))
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}
