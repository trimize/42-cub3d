/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:37:22 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/14 15:39:57 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_enemy_helper(t_cube *cub, t_enemy *enemy, t_sprite *sp)
{
	sp->sprite_x = (enemy->x) - (cub->player.x);
	sp->sprite_y = (enemy->y) - (cub->player.y);
	sp->plane_length = tan((cub->fov * (M_PI / 180.0)) / 2.0);
	sp->dir_x = cos(-cub->rr.angle_rad);
	sp->dir_y = sin(-cub->rr.angle_rad);
	sp->plane_x = -sp->dir_y * sp->plane_length;
	sp->plane_y = sp->dir_x * sp->plane_length;
	sp->inv_det = 1.0 / (sp->plane_x * sp->dir_y - sp->dir_x * sp->plane_y);
	sp->transform_x = sp->inv_det * (sp->dir_y * sp->sprite_x - sp->dir_x
			* sp->sprite_y) * enemy->scale;
	sp->transform_y = sp->inv_det * (-sp->plane_y * sp->sprite_x + sp->plane_x
			* sp->sprite_y) * enemy->scale;
	sp->sprite_screen_x = (int)((WIDTH / 2) * (1 + sp->transform_x
				/ sp->transform_y));
	sp->scaled_z_position = (int)(enemy->z_index / sp->transform_y);
	sp->sprite_height = abs((int)(HEIGHT / (sp->transform_y)));
	sp->draw_start_y = -sp->sprite_height / 2
		+ HEIGHT / 2 + sp->scaled_z_position;
	if (sp->draw_start_y < 0)
		sp->draw_start_y = 0;
	sp->draw_end_y = sp->sprite_height / 2 + HEIGHT / 2 + sp->scaled_z_position;
	if (sp->draw_end_y >= HEIGHT)
		sp->draw_end_y = HEIGHT - 1;
	sp->aspect_ratio = (double)enemy->txt.width / (double)enemy->txt.height;
	sp->sprite_width = abs((int)(sp->sprite_height * (sp->aspect_ratio)));
}

void	draw_enemy_helper2(t_cube *cub, t_enemy *enemy, t_sprite *sp)
{
	sp->tex_x = (int)(256 * (sp->stripe - (-sp->sprite_width / 2
					+ sp->sprite_screen_x)) * enemy->txt.width
			/ sp->sprite_width) / 256;
	if (sp->transform_y > 0 && sp->stripe > 0 && sp->stripe < WIDTH)
	{
		sp->y = sp->draw_start_y;
		while (sp->y < sp->draw_end_y)
		{
			sp->d = (sp->y - sp->scaled_z_position) * 256 - HEIGHT
				* 128 + sp->sprite_height * 128;
			sp->tex_y = ((sp->d * enemy->txt.height)
					/ sp->sprite_height) / 256;
			sp->color = *(int *)(enemy->txt.addr + ((sp->tex_x + (sp->tex_y
								* enemy->txt.width))
						* (enemy->txt.bits_per_pixel / 8)));
			if ((sp->color) != 0x0000FF)
				((int *)(cub->addr))[sp->y * (cub->line_length
						/ 4) + sp->stripe] = sp->color;
			sp->y++;
		}
	}
}

void	draw_enemy(t_cube *cub, t_enemy *enemy)
{
	t_sprite	sp;

	draw_enemy_helper(cub, enemy, &sp);
	sp.draw_start_x = -sp.sprite_width / 2 + sp.sprite_screen_x;
	enemy->draw_start = sp.draw_start_x;
	if (sp.draw_start_x < 0)
		sp.draw_start_x = 0;
	sp.draw_end_x = sp.sprite_width / 2 + sp.sprite_screen_x;
	enemy->draw_end = sp.draw_end_x;
	if (sp.draw_end_x >= WIDTH)
		sp.draw_end_x = WIDTH - 1;
	sp.stripe = sp.draw_start_x;
	while (sp.stripe < sp.draw_end_x)
	{
		if (cub->rays[WIDTH - sp.stripe].dist < enemy->dist || (cub->rays[WIDTH
					- sp.stripe].is_door && !cub->rays[WIDTH
					- sp.stripe].door->is_open && enemy->dist
				> cub->rays[WIDTH - sp.stripe].d_dist))
		{
			sp.stripe++;
			continue ;
		}
		draw_enemy_helper2(cub, enemy, &sp);
		sp.stripe++;
	}
}
