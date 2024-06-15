/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:40:15 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/15 18:04:11 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_ray(t_cube *cub)
{
	t_raycast ray;

	ray.ra = cub->rr.angle_rad;
	for (ray.r = 0; ray.r < 1; ray.r++)
	{
		ray.dof = 0;
		double aTan = -1 / tan(ray.ra);
		
		if (ray.ra > M_PI) //Player is looking up
		{
			ray.ry = (((int) cub->player.y >> 6 ) << 6 ) - 0.0001;
			ray.rx = (cub->player.y - ray.ry) * aTan + cub->player.x;
			ray.yo = -64;
			ray.xo = - ray.yo * aTan;
		}
		else if (ray.ra < M_PI) //Player is looking down
		{
			ray.ry = (((int) cub->player.y >> 6 ) << 6 ) - 0.0001;
			ray.rx = (cub->player.y - ray.ry) * aTan + cub->player.x;
			ray.yo = -64;
			ray.xo = - ray.yo * aTan;
		}
		else if (ray.ra == 0 || ray.ra == M_PI) //Player is looking left or right
		{
			ray.rx = cub->player.x;
			ray.ry = cub->player.y;
			ray.dof = 8;
		}
		
	}
}
