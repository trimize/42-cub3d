/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:18:11 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/02 14:27:47 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	hp_handler(t_cube *cub)
{
	if (cub->player.hp == 100)
		draw_xpm_hp(0, WIDTH / 60, HEIGHT / 1.1, cub);
	else if (cub->player.hp == 75 && cub->current_frame_num_hp <= 2)
	{
		if (cub->current_frame_num_hp < 2)
			animate_health_bar(cub, 2);
		draw_xpm_hp(cub->current_frame_num_hp, WIDTH / 60, HEIGHT / 1.1, cub);
	}
	else if (cub->player.hp == 50 && cub->current_frame_num_hp <= 4)
	{
		if (cub->current_frame_num_hp < 4)
			animate_health_bar(cub, 4);
		draw_xpm_hp(cub->current_frame_num_hp, WIDTH / 60, HEIGHT / 1.1, cub);
	}
	else if (cub->player.hp == 25 && cub->current_frame_num_hp <= 6)
	{
		if (cub->current_frame_num_hp < 6)
			animate_health_bar(cub, 6);
		draw_xpm_hp(cub->current_frame_num_hp, WIDTH / 60, HEIGHT / 1.1, cub);
	}
	else if (cub->player.hp == 0)
	{
		draw_xpm_hp(7, WIDTH / 60, HEIGHT / 1.1, cub);
		cub->current_frame_num_hp = 1;
	}
}
