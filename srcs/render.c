/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:48:17 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	color_background(t_cube *cub, int length, int ray_i)
{
	int	i;

	i = (HEIGHT - length) / 2;
	if (i < 0)
		return ;
	while (i >= 0)
		((int *)(cub->addr))[(i--) * (cub->line_length
				/ 4) + WIDTH - ray_i] = cub->c_rgb;
	i = (HEIGHT + length) / 2;
	if (i > HEIGHT)
		return ;
	while (i <= HEIGHT)
			((int *)(cub->addr))[(i++) * (cub->line_length
				/ 4) + WIDTH - ray_i] = cub->f_rgb;
}

void	draw_items(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < cub->weapon_counter)
	{
		if (cub->weapons[i].display == 1)
			draw_weapon(cub, i);
		i++;
	}
	i = 0;
	while (i < cub->items_counter)
	{
		if (cub->items[i].display == 1)
			draw_item(cub, cub->items[i]);
		i++;
	}
	i = 0;
	while (i < cub->dropped_index)
	{
		if (cub->dropped_items[i].display == 1)
			draw_item(cub, cub->dropped_items[i]);
		i++;
	}
}

void	render_game(t_cube *cub)
{
	int	i;

	i = 0;
	while (i <= WIDTH)
	{
		cast_ray(cub, i);
		i++;
	}
	i = 0;
	while (i < cub->enemy_counter)
	{
		draw_enemy(cub, &cub->all_enemies[i]);
		i++;
	}
	draw_items(cub);
}

void	render_3d(t_cube *cub, t_raycast *ray)
{
	draw_vertical_line(cub, ray);
}
