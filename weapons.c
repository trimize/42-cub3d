/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:17:31 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/28 18:20:31 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_w_slots(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < 4)
		cub->weapons_in_slot[i++] = 0;
	cub->weapons_in_slot[0] = 1;
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
}

void	sword_handler(t_cube *cub)
{
	if (cub->option_bool == -1 && cub->key.mouse_l == 1 && cub->weapons_in_slot[cub->player.weapon - 1] == 1)
	{
		update_animation(cub);
		draw_xpm_s_animation(cub->current_frame_num_sword, WIDTH / 2.5, HEIGHT / 4, cub);
		if (cub->current_frame_num_sword == 4)
		{
			cub->key.mouse_l = 0;
			cub->current_frame_num_sword = 0;
		}
	}
	else if (cub->weapons_in_slot[cub->player.weapon - 1] == 1)
		draw_xpm_s_animation(0, WIDTH / 2.5, HEIGHT / 4, cub);
}
