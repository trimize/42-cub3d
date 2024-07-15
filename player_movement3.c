/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:27:12 by trimize           #+#    #+#             */
/*   Updated: 2024/07/15 20:27:33 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_movement_a3(t_cube *cub)
{
	if (-cub->rr.angle_rad != M_PI / 2
		&& cub->map.map[(int)(cub->player.y
			- cub->player.speed * sin(-cub->rr.angle_rad
				+ M_PI / 2))][(int)cub->player.x] != '2')
		cub->player.y -= cub->player.speed
			* sin(-cub->rr.angle_rad + M_PI / 2);
}

void	player_movement_a4(t_cube *cub)
{
	if (-cub->rr.angle_rad != M_PI / 2
		&& cub->map.map[(int)cub->player.y]
		[(int)(cub->player.x - cub->player.speed
			* cos(-cub->rr.angle_rad + M_PI / 2))] != '2')
		cub->player.x -= cub->player.speed
			* cos(-cub->rr.angle_rad + M_PI / 2);
}

void	player_movement_a5(t_cube *cub)
{
	if (-cub->rr.angle_rad != M_PI / 2
		&& cub->map.map[(int)(cub->player.y - cub->player.speed
			* sin(-cub->rr.angle_rad + M_PI / 2))][(int)cub->player.x]
			!= '1' && can_walk(cub, (int)(cub->player.y - cub->player.speed
		* sin(-cub->rr.angle_rad + M_PI / 2)),
			(int)cub->player.x) && is_corner(cub,
			(int) cub->player.x, (int)(cub->player.y
				- cub->player.speed * sin(-cub->rr.angle_rad + M_PI / 2))))
		player_movement_a3(cub);
	else if (-cub->rr.angle_rad != M_PI / 2
		&& cub->map.map[(int)cub->player.y][(int)(cub->player.x
		- cub->player.speed * cos(-cub->rr.angle_rad + M_PI / 2))]
			!= '1' && can_walk(cub, (int) cub->player.y, (int)
		(cub->player.x - cub->player.speed * cos(-cub->rr.angle_rad
			+ M_PI / 2))) && !is_corner(cub,
			(int)(cub->player.x - cub->player.speed
				* cos(-cub->rr.angle_rad + M_PI / 2)),
					(int)cub->player.y))
		player_movement_a4(cub);
}

void	player_movement_a(t_cube *cub)
{
	if (cub->map.map[(int)(cub->player.y - (cub->player.speed
				* sin(-cub->rr.angle_rad + M_PI / 2)))][(int)
		(cub->player.x - (cub->player.speed
			* cos(-cub->rr.angle_rad + M_PI / 2)))]
			!= '1' && can_walk(cub, (int)(cub->player.y - (cub->player.speed
		* sin(-cub->rr.angle_rad + M_PI / 2))), (int)
			(cub->player.x - (cub->player.speed
			* cos(-cub->rr.angle_rad + M_PI / 2))))
				&& remove_corners(cub, (int)(cub->player.x
			- (cub->player.speed * cos(-cub->rr.angle_rad
				+ M_PI / 2))), (int)
				(cub->player.y - (cub->player.speed
					* sin(-cub->rr.angle_rad
						+ M_PI / 2)))))
		player_movement_a2(cub);
	else
		player_movement_a5(cub);
}

void	player_movement_d2(t_cube *cub)
{
	if (cub->map.map[(int)(cub->player.y + (cub->player.speed
				* sin(-cub->rr.angle_rad
					+ M_PI / 2)))][(int)(cub->player.x + (cub->player.speed
			* cos(-cub->rr.angle_rad + M_PI / 2)))] != '2')
	{	
		cub->player.y += cub->player.speed
			* sin(-cub->rr.angle_rad + M_PI / 2);
		cub->player.x += cub->player.speed
			* cos(-cub->rr.angle_rad + M_PI / 2);
	}
}
