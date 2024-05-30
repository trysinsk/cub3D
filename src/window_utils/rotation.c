/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <mevonuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:00:02 by mevonuk           #+#    #+#             */
/*   Updated: 2024/05/29 17:00:30 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_left(t_core *core)
{
	core->player->angle += ROTATION_SPEED;
	core->player->angle = normalize_angle(core->player->angle);
}

void	rotate_right(t_core *core)
{
	core->player->angle -= ROTATION_SPEED;
	core->player->angle = normalize_angle(core->player->angle);
}
