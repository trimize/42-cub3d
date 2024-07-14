/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:33:53 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/14 21:42:31 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	start_handler(t_cube *cub)
{
	update_animation_start(cub);
	draw_xpm_animation(cub->main_menu_start->current_frame,
		WIDTH / 2.2, HEIGHT / 1.1, cub->main_menu_start);
	if (cub->main_menu_start->current_frame == 18)
		cub->main_menu_start->current_frame = 0;
}

void	update_animation_died(t_cube *cub)
{

	if (cub->game_over[cub->game_over->current_frame].tmp_delay++
		== cub->game_over->delay)
	{
		cub->game_over[cub->game_over->current_frame].tmp_delay = 0;
		cub->game_over->current_frame++;
	}
}

void	died_handler(t_cube *cub)
{
	update_animation_died(cub);
	draw_xpm_animation(cub->game_over->current_frame,
		WIDTH / 2.8, HEIGHT / 3, cub->game_over);
	if (cub->game_over->current_frame == 10)
	{
		cub->game_over->current_frame = 0;
		cub->bg_bool = 1;
	}
}

void	update_animation_txt(t_txt *txt, t_door *door)
{
	if (txt[door->frame].tmp_delay++ == txt->delay)
	{
		txt[door->frame].tmp_delay = 0;
		door->frame++;
	}
}

t_txt	*txt_handler(t_cube *cub, t_txt *txt, int max_frame, t_raycast ray)
{
	update_animation_txt(txt, ray.door);
	if (ray.door->frame == max_frame)
	{
		cub->key.e = 0;
		ray.door->is_open = 1;
	}
	return (&txt[ray.door->frame]);
}
