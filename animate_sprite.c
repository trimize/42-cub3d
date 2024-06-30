/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: to <to@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:29:06 by trimize           #+#    #+#             */
/*   Updated: 2024/06/30 12:10:39 by to               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	update_animation(t_cube *cub)
{

	if (cub->sword_ani[cub->current_frame_num_sword].tmp_delay++ == cub->sword_delay)
	{
		cub->sword_ani[cub->current_frame_num_sword].tmp_delay = 0;
		cub->current_frame_num_sword++;
	}
	return (1);
}

void	update_animation_crossbow(t_cube *cub)
{

	if (cub->crossbow[cub->current_frame_num_cbow].tmp_delay++ == cub->cbow_delay)
	{
		cub->crossbow[cub->current_frame_num_cbow].tmp_delay = 0;
		cub->current_frame_num_cbow++;
	}
}

void	update_animation_dragon(t_cube *cub)
{

	if (cub->dragon[cub->current_frame_num_dra].tmp_delay++ == cub->dra_delay)
	{
		cub->dragon[cub->current_frame_num_dra].tmp_delay = 0;
		cub->current_frame_num_dra++;
	}
}

void	update_animation_explosion(t_cube *cub)
{

	if (cub->explosion[cub->current_frame_num_explo].tmp_delay++ == cub->explo_delay)
	{
		cub->explosion[cub->current_frame_num_explo].tmp_delay = 0;
		cub->current_frame_num_explo++;
	}
}

void	animate_health_bar(t_cube *cub, int limite)
{
	if (cub->txt[cub->current_frame_num_hp].tmp_delay++ == cub->hp_delay)
	{
		cub->txt[cub->current_frame_num_hp].tmp_delay = 0;
		if (cub->current_frame_num_hp == limite)
			;
		else
			cub->current_frame_num_hp++;
	}
}