/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:39:28 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/14 19:42:53 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

double	dist(double ax, double ay, double bx, double by)
{
	return (sqrt(((bx - ax) * (bx - ax)) + ((by - ay) * (by - ay))));
}

void	ch_helper2(t_cube *cub, t_raycast *ray, double px, double py)
{
	if (ray->my >= 0 && ray->mx >= 0 && ray->my < cub->map.rows
		&& ray->mx < cub->map.cols && cub->map.map[ray->my][ray->mx] == 'D'
		&& ray->hd_dist == 9999999)
	{
		ray->hdx = ray->rx;
		ray->hdy = ray->ry;
		ray->hd_dist = dist(px, py, ray->hdx, ray->hdy);
	}
	if (ray->my >= 0 && ray->mx >= 0 && ray->my < cub->map.rows
		&& ray->mx < cub->map.cols && (cub->map.map[ray->my]
			[ray->mx] == '1'))
	{
		ray->hx = ray->rx;
		ray->hy = ray->ry;
		ray->h_dist = dist(px, py, ray->hx, ray->hy);
		ray->dof = WIDTH;
	}
	else
	{
		ray->ry += ray->yo;
		ray->rx += ray->xo;
		ray->dof++;
	}
}

void	ch_helper(t_raycast *ray, double px, double py)
{
	double	atan;

	atan = -1 / tan(ray->ra);
	if (ray->ra < M_PI)
	{
		ray->ry = ((int)(py / TILE_SIZE)) * TILE_SIZE - 0.00001;
		ray->rx = px + (ray->ry - py) * atan;
		ray->yo = -TILE_SIZE;
		ray->xo = (ray->yo * atan);
	}
	else if (ray->ra > M_PI)
	{
		ray->ry = ((int)(py / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
		ray->rx = px + (ray->ry - py) * atan;
		ray->yo = TILE_SIZE;
		ray->xo = (ray->yo * atan);
	}
	else if (ray->ra == 0 || ray->ra == M_PI)
	{
		ray->rx = px;
		ray->ry = py;
		ray->dof = WIDTH;
	}
}

void	check_horizontal(t_cube *cub, t_raycast *ray)
{
	double	px;
	double	py;

	px = cub->player.x * TILE_SIZE;
	py = cub->player.y * TILE_SIZE;
	ch_helper(ray, px, py);
	while (ray->dof < WIDTH)
	{
		ray->mx = (int)(ray->rx / TILE_SIZE);
		ray->my = (int)(ray->ry / TILE_SIZE);
		ch_helper2(cub, ray, px, py);
	}
}

void	cv_helper2(t_cube *cub, t_raycast *ray, double px, double py)
{
	if (ray->my >= 0 && ray->mx >= 0 && ray->my < cub->map.rows
		&& ray->mx < cub->map.cols && cub->map.map[ray->my][ray->mx] == 'D'
		&& ray->vd_dist == 9999999)
	{
		ray->vdx = ray->rx;
		ray->vdy = ray->ry;
		ray->vd_dist = dist(px, py, ray->vdx, ray->vdy);
	}
	if (ray->my >= 0 && ray->mx >= 0 && ray->my < cub->map.rows
		&& ray->mx < cub->map.cols && (cub->map.map[ray->my]
			[ray->mx] == '1'))
	{
		ray->vx = ray->rx;
		ray->vy = ray->ry;
		ray->v_dist = dist(px, py, ray->vx, ray->vy);
		ray->dof = WIDTH;
	}
	else
	{
		ray->ry += ray->yo;
		ray->rx += ray->xo;
		ray->dof++;
	}
}

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
