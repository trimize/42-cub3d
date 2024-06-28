/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:29:06 by trimize           #+#    #+#             */
/*   Updated: 2024/06/28 16:23:35 by trimize          ###   ########.fr       */
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