/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:38:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_weapon_helper(t_cube *cub, int index, t_sprite *sp)
{
	sp->sprite_x = (cub->weapons[index].x) - (cub->player.x);
	sp->sprite_y = (cub->weapons[index].y) - (cub->player.y);
	sp->plane_length = tan((cub->fov * (M_PI / 180.0)) / 2.0);
	sp->dir_x = cos(-cub->rr.angle_rad);
	sp->dir_y = sin(-cub->rr.angle_rad);
	sp->plane_x = -sp->dir_y * sp->plane_length;
	sp->plane_y = sp->dir_x * sp->plane_length;
	sp->inv_det = 1.0 / (sp->plane_x * sp->dir_y - sp->dir_x * sp->plane_y);
	sp->transform_x = sp->inv_det * (sp->dir_y * sp->sprite_x - sp->dir_x
			* sp->sprite_y) * 2;
	sp->transform_y = sp->inv_det * (-sp->plane_y * sp->sprite_x + sp->plane_x
			* sp->sprite_y) * 2;
	sp->sprite_screen_x = (int)((WIDTH / 2) * (1 + sp->transform_x
				/ sp->transform_y));
	sp->scaled_z_position = (int)(800 / sp->transform_y);
	sp->sprite_height = abs((int)(HEIGHT / (sp->transform_y)));
	sp->draw_start_y = -sp->sprite_height / 2
		+ HEIGHT / 2 + sp->scaled_z_position;
	if (sp->draw_start_y < 0)
		sp->draw_start_y = 0;
	sp->draw_end_y = sp->sprite_height / 2 + HEIGHT / 2 + sp->scaled_z_position;
	if (sp->draw_end_y >= HEIGHT)
		sp->draw_end_y = HEIGHT - 1;
	sp->aspect_ratio = (double)cub->weapons[index].txt->width
		/ (double)cub->weapons[index].txt->height;
}

void	draw_weapon_helper2(t_cube *cub, int index, t_sprite *sp)
{
	sp->tex_x = (int)(256 * (sp->stripe - (-sp->sprite_width / 2
					+ sp->sprite_screen_x)) * cub->weapons[index].txt->width
			/ sp->sprite_width) / 256;
	if (sp->transform_y > 0 && sp->stripe > 0 && sp->stripe < WIDTH)
	{
		sp->y = sp->draw_start_y;
		while (sp->y < sp->draw_end_y)
		{
			sp->d = (sp->y - sp->scaled_z_position) * 256 - HEIGHT
				* 128 + sp->sprite_height * 128;
			sp->tex_y = ((sp->d * cub->weapons[index].txt->height)
					/ sp->sprite_height) / 256;
			sp->color = *(int *)(cub->weapons[index].txt->addr + ((sp->tex_x
							+ (sp->tex_y * cub->weapons[index].txt->width))
						* (cub->weapons[index].txt->bits_per_pixel / 8)));
			if ((sp->color) != 0x0000FF)
				((int *)(cub->addr))[sp->y * (cub->line_length
						/ 4) + sp->stripe] = sp->color;
			sp->y++;
		}
	}
}

void	draw_weapon(t_cube *cub, int index)
{
	t_sprite	sp;

	draw_weapon_helper(cub, index, &sp);
	sp.sprite_width = abs((int)(sp.sprite_height * (sp.aspect_ratio)));
	sp.draw_start_x = -sp.sprite_width / 2 + sp.sprite_screen_x;
	if (sp.draw_start_x < 0)
		sp.draw_start_x = 0;
	sp.draw_end_x = sp.sprite_width / 2 + sp.sprite_screen_x;
	if (sp.draw_end_x >= WIDTH)
		sp.draw_end_x = WIDTH - 1;
	sp.stripe = sp.draw_start_x;
	while (sp.stripe < sp.draw_end_x)
	{
		if (cub->rays[WIDTH - sp.stripe].dist < cub->weapons[index].dist
			|| (cub->rays[WIDTH - sp.stripe].is_door && !cub->rays[WIDTH
					- sp.stripe].door->is_open && cub->weapons[index].dist
				> cub->rays[WIDTH - sp.stripe].d_dist))
		{
			sp.stripe++;
			continue ;
		}
		draw_weapon_helper2(cub, index, &sp);
		sp.stripe++;
	}
}
