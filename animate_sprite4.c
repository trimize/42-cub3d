/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:33:24 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/14 21:42:28 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	update_animation_txt_r(t_txt *txt, t_door *door)
{
	if (txt[door->frame].tmp_delay++ == txt->delay)
	{
		txt[door->frame].tmp_delay = 0;
		door->frame--;
	}
}

t_txt	*txt_handler_r(t_cube *cub, t_txt *txt, t_raycast ray)
{
	update_animation_txt_r(txt, ray.door);
	if (ray.door->frame == 6)
	{
		ray.door->is_open = 0;
		ray.door->is_closing = 1;
	}
	else if (ray.door->frame == 0)
	{
		cub->key.e = 0;
		ray.door->is_closing = 0;
	}
	return (&txt[ray.door->frame]);
}

void	update_animation_idle(t_txt *txt)
{
	if (txt[txt->current_frame].tmp_delay++ == txt->delay)
	{
		txt[txt->current_frame].tmp_delay = 0;
		txt->current_frame++;
	}
}

t_txt	enemy_animation_handler(t_txt *txt, int max_frame)
{
	update_animation_idle(txt);
	if (txt->current_frame == max_frame)
		txt->current_frame = 0;
	return (txt[txt->current_frame]);
}

void	update_animation_atk(t_txt *txt)
{
	if (txt[txt->current_frame].tmp_delay++ == txt->delay)
	{
		txt[txt->current_frame].tmp_delay = 0;
		txt->current_frame++;
	}
}
