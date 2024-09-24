/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:41:17 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 16:41:49 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cv_helper(t_raycast *ray, double px, double py)
{
	double	ntan;

	ntan = -tan(ray->ra);
	if (ray->ra > M_PI / 2 && ray->ra < ((3 * M_PI) / 2))
	{
		ray->rx = ((int)(px / TILE_SIZE)) * TILE_SIZE - 0.00001;
		ray->ry = (py + (ray->rx - px) * ntan);
		ray->xo = -TILE_SIZE;
		ray->yo = (ray->xo * ntan);
	}
	else if (ray->ra < M_PI / 2 || ray->ra > ((3 * M_PI) / 2))
	{
		ray->rx = ((int)(px / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
		ray->ry = (py + (ray->rx - px) * ntan);
		ray->xo = TILE_SIZE;
		ray->yo = (ray->xo * ntan);
	}
	else if (ray->ra == 0 || ray->ra == M_PI)
	{
		ray->rx = px;
		ray->ry = py;
		ray->dof = WIDTH;
	}
}

void	check_vertical(t_cube *cub, t_raycast *ray)
{
	double	px;
	double	py;

	px = cub->player.x * TILE_SIZE;
	py = cub->player.y * TILE_SIZE;
	cv_helper(ray, px, py);
	while (ray->dof < WIDTH)
	{
		ray->mx = (int)(ray->rx / TILE_SIZE);
		ray->my = (int)(ray->ry / TILE_SIZE);
		cv_helper2(cub, ray, px, py);
	}
}
