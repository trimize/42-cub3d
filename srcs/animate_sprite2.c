/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:32:28 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:39:52 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_animation_crown(t_txt *txt)
{
	if (txt[txt->current_frame].tmp_delay++ == txt->delay)
	{
		txt[txt->current_frame].tmp_delay = 0;
		txt->current_frame++;
	}
}

t_txt	*crown_handler(t_txt *txt)
{
	update_animation_crown(txt);
	if (txt->current_frame == txt->frame_max)
		txt->current_frame = 0;
	return (&txt[txt->current_frame]);
}

void	update_animation_general(t_txt *txt)
{
	if (txt[txt->current_frame].tmp_delay++ == txt->delay)
	{
		txt[txt->current_frame].tmp_delay = 0;
		txt->current_frame++;
	}
}

void	animation_handler(t_txt *txt, t_cube *cub, int x, int y)
{
	(void) cub;
	update_animation_general(txt);
	draw_xpm_animation(txt->current_frame, x, y, txt);
	if (txt->current_frame == txt->frame_max)
		txt->current_frame = 0;
}

void	fade_to_black(t_cube *cub, double fade_factor, int bits_per_pixel)
{
	int	i;
	int	j;
	int	color;
	int	*pixel;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			pixel = (int *)(cub->addr + (i * cub->line_length
						+ j * bits_per_pixel / 8));
			color = *pixel;
			cub->fade_r = (color >> 16) & 0xFF;
			cub->fade_g = (color >> 8) & 0xFF;
			cub->fade_b = color & 0xFF;
			cub->fade_r = (cub->fade_r * fade_factor);
			cub->fade_g = (cub->fade_g * fade_factor);
			cub->fade_b = (cub->fade_b * fade_factor);
			*pixel = (cub->fade_r << 16) | (cub->fade_g << 8) | cub->fade_b;
			j++;
		}
		i++;
	}
}
