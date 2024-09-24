/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:40:15 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_ray_helper3(t_raycast *ray)
{
	if (ray->vd_dist < ray->hd_dist)
	{
		ray->d_dist = ray->vd_dist;
		ray->dx = ray->vdx;
		ray->dy = ray->vdy;
		if (ray->ra > M_PI / 2 && ray->ra < ((3 * M_PI) / 2))
			ray->door_flag = 'W';
		else
			ray->door_flag = 'E';
	}
	else
	{
		ray->d_dist = ray->hd_dist;
		ray->dx = ray->hdx;
		ray->dy = ray->hdy;
		if (ray->ra < M_PI)
			ray->door_flag = 'N';
		else
			ray->door_flag = 'S';
	}
}

void	cast_ray_helper2(t_raycast *ray)
{
	if (ray->v_dist < ray->h_dist)
	{
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		ray->dist = ray->v_dist;
		if (ray->ra > M_PI / 2 && ray->ra < ((3 * M_PI) / 2))
			ray->flag = 'W';
		else
			ray->flag = 'E';
	}
	else
	{
		ray->rx = ray->hx;
		ray->ry = ray->hy;
		ray->dist = ray->h_dist;
		if (ray->ra < M_PI)
			ray->flag = 'N';
		else
			ray->flag = 'S';
	}
	cast_ray_helper3(ray);
}

void	cast_ray_helper(t_cube *cub, t_raycast *ray, int index)
{
	ray->ra = cub->rr.angle_rad;
	ray->r = index;
	ray->ra = cub->rr.angle_rad + (index - WIDTH / 2)
		* (cub->fov * 0.0174533 / WIDTH);
	if (ray->ra < 0)
		ray->ra += 2 * M_PI;
	else if (ray->ra > 2 * M_PI)
		ray->ra -= 2 * M_PI;
	ray->dof = 0;
	ray->is_door = 0;
	ray->h_dist = 9999999;
	ray->d_dist = 9999999;
	ray->vd_dist = 9999999;
	ray->hd_dist = 9999999;
	ray->hx = cub->player.x * TILE_SIZE;
	ray->hy = cub->player.y * TILE_SIZE;
	check_horizontal(cub, ray);
	ray->dof = 0;
	ray->v_dist = 9999999;
	ray->vx = cub->player.x * TILE_SIZE;
	ray->vy = cub->player.y * TILE_SIZE;
	check_vertical(cub, ray);
	cast_ray_helper2(ray);
}

void	cast_ray(t_cube *cub, int index)
{
	t_raycast	ray;

	cast_ray_helper(cub, &ray, index);
	if (ray.d_dist < ray.dist)
	{
		ray.is_door = 1;
		ray.door = search_door(cub, (int) ray.dx
				/ TILE_SIZE, (int) ray.dy / TILE_SIZE);
	}
	cub->rays[index].rx = ray.rx;
	cub->rays[index].ry = ray.ry;
	cub->rays[index].dist = ray.dist;
	cub->rays[index].d_dist = ray.d_dist;
	cub->rays[index].r = index;
	cub->rays[index].door = ray.door;
	cub->rays[index].is_door = ray.is_door;
	cub->rays[index].dx = ray.dx;
	cub->rays[index].dy = ray.dy;
	render_3d(cub, &ray);
}
