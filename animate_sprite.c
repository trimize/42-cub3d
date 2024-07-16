/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:29:06 by trimize           #+#    #+#             */
/*   Updated: 2024/07/16 16:52:22 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	update_animation(t_cube *cub)
{
	if (cub->sword_ani[cub->sword_ani->current_frame].tmp_delay++
		== cub->sword_ani->delay)
	{
		cub->sword_ani[cub->sword_ani->current_frame].tmp_delay = 0;
		cub->sword_ani->current_frame++;
	}
	return (1);
}

void	update_animation_crossbow(t_cube *cub)
{
	if (cub->crossbow[cub->crossbow->current_frame].tmp_delay++
		== cub->crossbow->delay)
	{
		cub->crossbow[cub->crossbow->current_frame].tmp_delay = 0;
		cub->crossbow->current_frame++;
	}
}

void	update_animation_dragon(t_cube *cub)
{
	if (cub->dragon[cub->dragon->current_frame].tmp_delay++
		== cub->dragon->delay)
	{
		cub->dragon[cub->dragon->current_frame].tmp_delay = 0;
		cub->dragon->current_frame++;
	}
}

void	update_animation_explosion(t_cube *cub)
{
	if (cub->explosion[cub->explosion->current_frame].tmp_delay++
		== cub->explosion->delay)
	{
		cub->explosion[cub->explosion->current_frame].tmp_delay = 0;
		cub->explosion->current_frame++;
	}
}

void	animate_health_bar(t_cube *cub, int limite)
{
	if (cub->hp_frame[cub->hp_frame->current_frame].tmp_delay++
		== cub->hp_frame->delay)
	{
		cub->hp_frame[cub->hp_frame->current_frame].tmp_delay = 0;
		if (cub->hp_frame->current_frame == limite)
			;
		else
			cub->hp_frame->current_frame++;
	}
}
