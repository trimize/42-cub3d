/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:25:42 by trimize           #+#    #+#             */
/*   Updated: 2024/07/15 20:26:04 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_movement_s3(t_cube *cub)
{
	if (-cub->rr.angle_rad != 3 * M_PI / 2
		&& cub->map.map[(int)(cub->player.y
			+ cub->player.speed
			* sin(-cub->rr.angle_rad))]
				[(int) cub->player.x] != '2')
		cub->player.y -= cub->player.speed
			* sin(-cub->rr.angle_rad);
}

void	player_movement_s4(t_cube *cub)
{
	if (-cub->rr.angle_rad != 3 * M_PI / 2
		&& cub->map.map[(int)cub->player.y]
		[(int)(cub->player.x - cub->player.speed
			* cos(-cub->rr.angle_rad))] != '2')
		cub->player.x -= cub->player.speed
			* cos(-cub->rr.angle_rad);
}

void	player_movement_s5(t_cube *cub)
{
	if (-cub->rr.angle_rad != 3 * M_PI / 2
		&& cub->map.map[(int)(cub->player.y - cub->player.speed
			* sin(-cub->rr.angle_rad))][(int) cub->player.x]
		!= '1' && can_walk(cub,
	(int)(cub->player.y - cub->player.speed
		* sin(-cub->rr.angle_rad)), (int)cub->player.x)
		&& is_corner(cub, (int) cub->player.x,
			(int)(cub->player.y - cub->player.speed
				* sin(-cub->rr.angle_rad))))
		player_movement_s3(cub);
	else if (-cub->rr.angle_rad != 3 * M_PI / 2
		&& cub->map.map[(int)cub->player.y][(int)
		(cub->player.x - cub->player.speed
			* cos(-cub->rr.angle_rad))] != '1' && can_walk(cub,
	(int)cub->player.y, (int)(cub->player.x
		- cub->player.speed * cos(-cub->rr.angle_rad)))
		&& is_corner(cub, (int)(cub->player.x - cub->player.speed
			* cos(-cub->rr.angle_rad)), (int)cub->player.y))
		player_movement_s4(cub);
}

void	player_movement_s(t_cube *cub)
{
	if (cub->map.map[(int)(cub->player.y - (cub->player.speed * sin(-cub
					->rr.angle_rad)))][(int)(cub->player.x - (cub->player.speed
		* cos(-cub->rr.angle_rad)))] != '1' && can_walk(cub,
			(int)(cub->player.y - (cub->player.speed
				* sin(-cub->rr.angle_rad))),
		(int)(cub->player.x - (cub->player.speed * cos(-cub->rr.angle_rad))))
			&& remove_corners(cub, (int)(cub->player.x
			- (cub->player.speed * cos(-cub->rr.angle_rad))),
				(int)(cub->player.y - (cub->player.speed
					* sin(-cub->rr.angle_rad)))))
		player_movement_s2(cub);
	else
		player_movement_s5(cub);
}

void	player_movement_a2(t_cube *cub)
{
	if (cub->map.map[(int)(cub->player.y - (cub->player.speed
				* sin(-cub->rr.angle_rad
					+ M_PI / 2)))][(int)(cub->player.x
			- (cub->player.speed
			* cos(-cub->rr.angle_rad + M_PI / 2)))] != '2')
	{
		cub->player.y -= cub->player.speed
			* sin(-cub->rr.angle_rad + M_PI / 2);
		cub->player.x -= cub->player.speed
			* cos(-cub->rr.angle_rad + M_PI / 2);
	}
}
