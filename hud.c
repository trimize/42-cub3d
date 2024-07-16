/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:18:11 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 15:45:31 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	hp_helper(t_cube *cub)
{
	if (cub->hp_frame->current_frame < 2)
		animate_health_bar(cub, 2);
	draw_xpm_hp(cub->hp_frame->current_frame,
		WIDTH / 60, HEIGHT / 1.1, cub);
}

void	hp_handler(t_cube *cub)
{
	if (cub->player.hp == 100)
		draw_xpm_hp(0, WIDTH / 60, HEIGHT / 1.1, cub);
	else if (cub->player.hp == 75 && cub->hp_frame->current_frame <= 2)
		hp_helper(cub);
	else if (cub->player.hp == 50 && cub->hp_frame->current_frame <= 4)
	{
		if (cub->hp_frame->current_frame < 4)
			animate_health_bar(cub, 4);
		draw_xpm_hp(cub->hp_frame->current_frame,
			WIDTH / 60, HEIGHT / 1.1, cub);
	}
	else if (cub->player.hp == 25 && cub->hp_frame->current_frame <= 6)
	{
		if (cub->hp_frame->current_frame < 6)
			animate_health_bar(cub, 6);
		draw_xpm_hp(cub->hp_frame->current_frame,
			WIDTH / 60, HEIGHT / 1.1, cub);
	}
	else if (cub->player.hp == 0)
	{
		draw_xpm_hp(7, WIDTH / 60, HEIGHT / 1.1, cub);
		cub->hp_frame->current_frame = 1;
	}
}
