/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:29:06 by trimize           #+#    #+#             */
/*   Updated: 2024/07/03 20:02:05 by mbrandao         ###   ########.fr       */
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
void	update_animation_title(t_cube *cub)
{

	if (cub->title_screen[cub->current_frame_num_title].tmp_delay++ == cub->title_delay)
		cub->current_frame_num_title++;
}

void	title_handler(t_cube *cub)
{
	if (cub->title_bool == 1)
	{
		update_animation_title(cub);
		draw_xpm_animation(cub->current_frame_num_title, WIDTH / 6, HEIGHT / 3, cub, cub->title_screen);
		if (cub->current_frame_num_title == 28)
		{
			cub->title_bool = 0;
			cub->bg_bool = 1;
		}
	}
}

void	update_animation_bg(t_cube *cub)
{

	if (cub->main_menu_bg[cub->current_frame_num_bg].tmp_delay++ == cub->bg_delay)
	{
		cub->main_menu_bg[cub->current_frame_num_bg].tmp_delay = 0;
		cub->current_frame_num_bg++;
	}
}

void	bg_handler(t_cube *cub)
{
	update_animation_bg(cub);
	draw_xpm_animation(cub->current_frame_num_bg, 0, 0, cub, cub->main_menu_bg);
	if (cub->current_frame_num_bg == 22)
		cub->current_frame_num_bg = 0;
}

void	update_animation_start(t_cube *cub)
{

	if (cub->main_menu_start[cub->current_frame_num_start].tmp_delay++ == cub->start_delay)
	{
		cub->main_menu_start[cub->current_frame_num_start].tmp_delay = 0;
		cub->current_frame_num_start++;
	}
}

void	start_handler(t_cube *cub)
{
	update_animation_start(cub);
	draw_xpm_animation(cub->current_frame_num_start, WIDTH / 2.2, HEIGHT / 1.1, cub, cub->main_menu_start);
	if (cub->current_frame_num_start == 18)
		cub->current_frame_num_start = 0;
}

void	update_animation_died(t_cube *cub)
{

	if (cub->game_over[cub->current_frame_num_died].tmp_delay++ == cub->died_delay)
	{
		cub->game_over[cub->current_frame_num_died].tmp_delay = 0;
		cub->current_frame_num_died++;
	}
}

void	died_handler(t_cube *cub)
{
	update_animation_died(cub);
	draw_xpm_animation(cub->current_frame_num_died, WIDTH / 2.8, HEIGHT / 3, cub, cub->game_over);
	if (cub->current_frame_num_died == 10)
	{
		cub->current_frame_num_died = 0;
		cub->bg_bool = 1;
		cub->enter_pressed = 0;
	}
}

void fade_to_black(t_cube *cub, double fade_factor, int	bits_per_pixel)
{
    int i, j;
    int color;
    unsigned char r, g, b;
    int *pixel;
    int bytes_per_pixel = bits_per_pixel / 8;

    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            pixel = (int *)(cub->addr + (i * cub->line_length + j * bytes_per_pixel));
            color = *pixel;

            // Extract the RGB components
            r = (color >> 16) & 0xFF;
            g = (color >> 8) & 0xFF;
            b = color & 0xFF;

            // Apply the fade factor
            r = (r * fade_factor);
            g = (g * fade_factor);
            b = (b * fade_factor);

            // Recombine the RGB components into a single color value
            *pixel = (r << 16) | (g << 8) | b;
        }
    }
}
