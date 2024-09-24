/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:34:20 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:39:52 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_animation_title(t_cube *cub)
{
	if (cub->title_screen[cub->title_screen->current_frame].tmp_delay++
		== cub->title_screen->delay)
	{
		cub->title_screen[cub->title_screen->current_frame].tmp_delay = 0;
		cub->title_screen->current_frame++;
	}
}

void	title_handler(t_cube *cub)
{
	if (cub->title_bool == 1)
	{
		update_animation_title(cub);
		draw_xpm_animation(cub->title_screen->current_frame,
			WIDTH / 6, HEIGHT / 3, cub->title_screen);
		if (cub->title_screen->current_frame == 28)
		{
			cub->title_bool = 0;
			cub->bg_bool = 1;
		}
	}
}

void	update_animation_bg(t_cube *cub)
{
	if (cub->main_menu_bg[cub->main_menu_bg->current_frame].tmp_delay++
		== cub->main_menu_bg->delay)
	{
		cub->main_menu_bg[cub->main_menu_bg->current_frame].tmp_delay = 0;
		cub->main_menu_bg->current_frame++;
	}
}

void	bg_handler(t_cube *cub)
{
	update_animation_bg(cub);
	draw_xpm_animation(cub->main_menu_bg->current_frame,
		0, 0, cub->main_menu_bg);
	if (cub->main_menu_bg->current_frame == 22)
		cub->main_menu_bg->current_frame = 0;
}

void	update_animation_start(t_cube *cub)
{
	if (cub->main_menu_start[cub->main_menu_start->current_frame].tmp_delay++
		== cub->main_menu_start->delay)
	{
		cub->main_menu_start[cub->main_menu_start->current_frame].tmp_delay = 0;
		cub->main_menu_start->current_frame++;
	}
}
