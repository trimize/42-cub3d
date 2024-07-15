/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:16:09 by trimize           #+#    #+#             */
/*   Updated: 2024/07/15 18:17:33 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	player_rotation_init(t_cube *cub)
{
	cub->start = 0;
	if (cub->player.dir == 0)
		cub->rr.angle_rad = M_PI / 2;
	else if (cub->player.dir == 1)
		cub->rr.angle_rad = 0;
	else if (cub->player.dir == 2)
		cub->rr.angle_rad = (3 * M_PI) / 2;
	else if (cub->player.dir == 3)
		cub->rr.angle_rad = M_PI;
}

void	rotate_player(t_cube *cub, double dir)
{
	cub->rr.angle_rad += dir;
	if (cub->rr.angle_rad < 0)
		cub->rr.angle_rad += 2 * M_PI;
	else if (cub->rr.angle_rad > 2 * M_PI)
		cub->rr.angle_rad -= 2 * M_PI;
}
