/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: to <to@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:17:31 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/30 12:42:04 by to               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_w_slots(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < 4)
		cub->weapons_in_slot[i++] = 0;
	//just to test
	cub->weapons_in_slot[0] = 1;
	cub->weapons_in_slot[1] = 2;
	cub->weapons_in_slot[2] = 3;
	cub->weapons_in_slot[3] = 4;
}

void	weapon_slot_handler(t_cube *cub)
{
	if (cub->player.weapon == 1)
		draw_xpm_texture(8, WIDTH / 60, HEIGHT / 1.2, cub);
	else
		draw_xpm_texture(7, WIDTH / 60, HEIGHT / 1.2, cub);
	if (cub->player.weapon == 2)
		draw_xpm_texture(8, WIDTH / 19, HEIGHT / 1.2, cub);
	else
		draw_xpm_texture(7, WIDTH / 19, HEIGHT / 1.2, cub);
	if (cub->player.weapon == 3)
		draw_xpm_texture(8, WIDTH / 11.3, HEIGHT / 1.2, cub);
	else
		draw_xpm_texture(7, WIDTH / 11.3, HEIGHT / 1.2, cub);
	if (cub->player.weapon == 4)
		draw_xpm_texture(8, WIDTH / 8.05, HEIGHT / 1.2, cub);
	else
		draw_xpm_texture(7, WIDTH / 8.05, HEIGHT / 1.2, cub);
	if (cub->weapons_in_slot[0] == 1)
		draw_xpm_texture(9, WIDTH / 35, HEIGHT / 1.19, cub);
	else if (cub->weapons_in_slot[0] == 2)
		draw_xpm_texture(11, WIDTH / 47, HEIGHT / 1.185, cub);
	else if (cub->weapons_in_slot[0] == 3)
		draw_xpm_texture(13, WIDTH / 41.2, HEIGHT / 1.185, cub);
	else if (cub->weapons_in_slot[0] == 4)
		draw_xpm_texture(14, WIDTH / 50, HEIGHT / 1.191, cub);
	if (cub->weapons_in_slot[1] == 1)
		draw_xpm_texture(9, WIDTH / 15.4, HEIGHT / 1.19, cub);
	else if (cub->weapons_in_slot[1] == 2)
		draw_xpm_texture(11, WIDTH / 18, HEIGHT / 1.185, cub);
	else if (cub->weapons_in_slot[1] == 3)
		draw_xpm_texture(13, WIDTH / 16.6, HEIGHT / 1.185, cub);
	else if (cub->weapons_in_slot[1] == 4)
		draw_xpm_texture(14, WIDTH / 18, HEIGHT / 1.191, cub);
	if (cub->weapons_in_slot[2] == 1)
		draw_xpm_texture(9, WIDTH / 9.9, HEIGHT / 1.19, cub);
	else if (cub->weapons_in_slot[2] == 2)
		draw_xpm_texture(11, WIDTH / 10.9, HEIGHT / 1.185, cub);
	else if (cub->weapons_in_slot[2] == 3)
		draw_xpm_texture(13, WIDTH / 10.399, HEIGHT / 1.185, cub);
	else if (cub->weapons_in_slot[2] == 4)
		draw_xpm_texture(14, WIDTH / 10.9, HEIGHT / 1.191, cub);
	if (cub->weapons_in_slot[3] == 1)
		draw_xpm_texture(9, WIDTH / 7.3, HEIGHT / 1.19, cub);
	else if (cub->weapons_in_slot[3] == 2)
		draw_xpm_texture(11, WIDTH / 7.8, HEIGHT / 1.185, cub);
	else if (cub->weapons_in_slot[3] == 3)
		draw_xpm_texture(13, WIDTH / 7.57, HEIGHT / 1.185, cub);
	else if (cub->weapons_in_slot[3] == 4)
		draw_xpm_texture(14, WIDTH / 7.8, HEIGHT / 1.191, cub);
}

void	sword_handler(t_cube *cub)
{
	if (cub->option_bool == -1 && cub->key.mouse_l == 1 && cub->weapons_in_slot[cub->player.weapon - 1] == 1)
	{
		update_animation(cub);
		draw_xpm_animation(cub->current_frame_num_sword, WIDTH / 2.5, HEIGHT / 4, cub, cub->sword_ani);
		if (cub->current_frame_num_sword == 4)
		{
			cub->key.mouse_l = 0;
			cub->current_frame_num_sword = 0;
		}
	}
	else if (cub->weapons_in_slot[cub->player.weapon - 1] == 1)
		draw_xpm_animation(0, WIDTH / 2.5, HEIGHT / 4, cub, cub->sword_ani);
}

void	crossbow_handler(t_cube *cub)
{
	if (cub->option_bool == -1 && cub->key.mouse_l == 1 && cub->weapons_in_slot[cub->player.weapon - 1] == 2 && cub->player.arrows > 0)
	{
		update_animation_crossbow(cub);
		draw_xpm_animation(cub->current_frame_num_cbow, WIDTH / 2.8, HEIGHT / 1.255, cub, cub->crossbow);
		if (cub->current_frame_num_cbow == 5)
		{
			cub->key.mouse_l = 0;
			cub->current_frame_num_cbow = 0;
			cub->player.arrows--;
		}
	}
	else if (cub->weapons_in_slot[cub->player.weapon - 1] == 2)
		draw_xpm_animation(0, WIDTH / 2.8, HEIGHT / 1.255, cub, cub->crossbow);
}

void	shield_handler(t_cube *cub)
{
	if (cub->weapons_in_slot[cub->player.weapon - 1] == 3)
		draw_xpm_texture(12, WIDTH / 1.8, HEIGHT / 1.9, cub);
}

void	dragon_handler(t_cube *cub)
{
	if (cub->weapons_in_slot[cub->player.weapon - 1] == 4)
	{
		update_animation_dragon(cub);
		draw_xpm_animation(cub->current_frame_num_dra, WIDTH / 1.6, HEIGHT / 2.2, cub, cub->dragon);
		if (cub->current_frame_num_dra == 4)
			cub->current_frame_num_dra = 0;
	}
}

void	explosion_handler(t_cube *cub)
{
	if (cub->option_bool == -1 && cub->key.mouse_l == 1 && cub->weapons_in_slot[cub->player.weapon - 1] == 4)
	{
		update_animation_explosion(cub);
		draw_xpm_animation(cub->current_frame_num_explo, WIDTH / 2.7, HEIGHT / 3.5, cub, cub->explosion);
		if (cub->current_frame_num_explo == 12)
		{
			cub->current_frame_num_explo = 0;
			cub->key.mouse_l = 0;
		}
	}
}
