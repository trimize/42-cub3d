/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:31:16 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_helper4(t_vert *vert)
{
	if (vert->b_pix > HEIGHT)
		vert->b_pix = HEIGHT;
	if (vert->t_pix < 0)
		vert->t_pix = 0;
	vert->y_o = (vert->t_pix - (HEIGHT / 2)
			+ (vert->length / 2)) * vert->factor;
}

void	draw_helper3(t_cube *cub, t_raycast *ray, t_vert *vert)
{
	vert->dist = ray->dist;
	vert->x = ray->rx;
	vert->y = ray->ry;
	vert->length = (int)(WALL_SIZE * (1 / vert->dist));
	ray->txt = &cub->txt[search_txt(cub, ray->flag)];
	vert->txt_addr = (int *)ray->txt->addr;
	vert->factor = (double)ray->txt->height / vert->length;
	if (ray->flag == 'N' || ray->flag == 'S')
	{
		vert->x_o = (int)fmod(vert->x, TILE_SIZE)
			* ray->txt->width / TILE_SIZE;
		if (ray->flag == 'S')
			vert->x_o = ray->txt->width - vert->x_o - 1;
	}
	else
	{
		vert->x_o = (int)fmod(vert->y, TILE_SIZE)
			* ray->txt->width / TILE_SIZE;
		if (ray->flag == 'W')
			vert->x_o = ray->txt->width - vert->x_o - 1;
	}
	vert->t_pix = (HEIGHT / 2) - (vert->length / 2);
	vert->b_pix = (HEIGHT / 2) + (vert->length / 2);
	draw_helper4(vert);
}

void	draw_helper2(t_raycast *ray, t_vert *vert)
{
	if (ray->is_door && !ray->door->is_open
		&& (ray->door_flag == 'N' || ray->door_flag == 'S'))
	{
		vert->x_o = (int)fmod(vert->x, TILE_SIZE) * ray->txt->width / TILE_SIZE;
		if (ray->door_flag == 'S')
			vert->x_o = ray->txt->width - vert->x_o - 1;
	}
	else if (ray->is_door && !ray->door->is_open)
	{
		vert->x_o = (int)fmod(vert->y, TILE_SIZE) * ray->txt->width / TILE_SIZE;
		if (ray->door_flag == 'W')
			vert->x_o = ray->txt->width - vert->x_o - 1;
	}
	vert->t_pix = (HEIGHT / 2) - (vert->length / 2);
	vert->b_pix = (HEIGHT / 2) + (vert->length / 2);
	if (vert->b_pix > HEIGHT)
		vert->b_pix = HEIGHT;
	if (vert->t_pix < 0)
		vert->t_pix = 0;
	vert->y_o = (vert->t_pix - (HEIGHT / 2)
			+ (vert->length / 2)) * vert->factor;
}

void	draw_helper(t_cube *cub, t_raycast *ray, t_vert *vert)
{
	if (ray->is_door && !ray->door->is_open)
	{
		vert->dist = ray->d_dist;
		vert->x = ray->dx;
		vert->y = ray->dy;
	}
	vert->length = (int)(WALL_SIZE * (1 / vert->dist));
	ray->txt = &cub->txt[search_txt(cub, ray->flag)];
	if (ray->is_door && !ray->door->is_open)
		ray->txt = ray->door->txt;
	vert->txt_addr = (int *)ray->txt->addr;
	vert->factor = (double)ray->txt->height / vert->length;
	if (ray->flag == 'N' || ray->flag == 'S')
	{
		vert->x_o = (int)fmod(vert->x, TILE_SIZE) * ray->txt->width / TILE_SIZE;
		if (ray->flag == 'S')
			vert->x_o = ray->txt->width - vert->x_o - 1;
	}
	else
	{
		vert->x_o = (int)fmod(vert->y, TILE_SIZE) * ray->txt->width / TILE_SIZE;
		if (ray->flag == 'W')
			vert->x_o = ray->txt->width - vert->x_o - 1;
	}
	draw_helper2(ray, vert);
}

void	draw_vertical_line(t_cube *cub, t_raycast *ray)
{
	t_vert	vert;

	vert.dist = ray->dist;
	vert.x = ray->rx;
	vert.y = ray->ry;
	draw_helper(cub, ray, &vert);
	while (vert.t_pix < vert.b_pix)
	{
		vert.tex_y = (int)vert.y_o & (ray->txt->height - 1);
		vert.color = vert.txt_addr[vert.tex_y * (
				ray->txt->line_length / 4) + (int)vert.x_o];
		if (vert.color == 0x0000FF)
		{
			draw_helper3(cub, ray, &vert);
			continue ;
		}
		((int *)(cub->addr))[vert.t_pix * (cub->line_length
				/ 4) + WIDTH - ray->r] = vert.color;
		vert.y_o += vert.factor;
		vert.t_pix++;
	}
	cub->rays[ray->r].txt = ray->txt;
	color_background(cub, vert.length, ray->r);
}
