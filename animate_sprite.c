/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:29:06 by trimize           #+#    #+#             */
/*   Updated: 2024/07/13 14:32:52 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	update_animation(t_cube *cub)
{

	if (cub->sword_ani[cub->sword_ani->current_frame].tmp_delay++ == cub->sword_ani->delay)
	{
		cub->sword_ani[cub->sword_ani->current_frame].tmp_delay = 0;
		cub->sword_ani->current_frame++;
	}
	return (1);
}

void	update_animation_crossbow(t_cube *cub)
{

	if (cub->crossbow[cub->crossbow->current_frame].tmp_delay++ == cub->crossbow->delay)
	{
		cub->crossbow[cub->crossbow->current_frame].tmp_delay = 0;
		cub->crossbow->current_frame++;
	}
}

void	update_animation_dragon(t_cube *cub)
{

	if (cub->dragon[cub->dragon->current_frame].tmp_delay++ == cub->dragon->delay)
	{
		cub->dragon[cub->dragon->current_frame].tmp_delay = 0;
		cub->dragon->current_frame++;
	}
}

void	update_animation_explosion(t_cube *cub)
{

	if (cub->explosion[cub->explosion->current_frame].tmp_delay++ == cub->explosion->delay)
	{
		cub->explosion[cub->explosion->current_frame].tmp_delay = 0;
		cub->explosion->current_frame++;
	}
}

void	animate_health_bar(t_cube *cub, int limite)
{
	if (cub->hp_frame[cub->hp_frame->current_frame].tmp_delay++ == cub->hp_frame->delay)
	{
		cub->hp_frame[cub->hp_frame->current_frame].tmp_delay = 0;
		if (cub->hp_frame->current_frame == limite)
			;
		else
			cub->hp_frame->current_frame++;
	}
}

void	update_animation_title(t_cube *cub)
{
	if (cub->title_screen[cub->title_screen->current_frame].tmp_delay++ == cub->title_screen->delay)
		cub->title_screen->current_frame++;
}

void	title_handler(t_cube *cub)
{
	if (cub->title_bool == 1)
	{
		update_animation_title(cub);
		draw_xpm_animation(cub->title_screen->current_frame, WIDTH / 6, HEIGHT / 3, cub, cub->title_screen);
		if (cub->title_screen->current_frame == 28)
		{
			cub->title_bool = 0;
			cub->bg_bool = 1;
		}
	}
}

void	update_animation_bg(t_cube *cub)
{

	if (cub->main_menu_bg[cub->main_menu_bg->current_frame].tmp_delay++ == cub->main_menu_bg->delay)
	{
		cub->main_menu_bg[cub->main_menu_bg->current_frame].tmp_delay = 0;
		cub->main_menu_bg->current_frame++;
	}
}

void	bg_handler(t_cube *cub)
{
	update_animation_bg(cub);
	draw_xpm_animation(cub->main_menu_bg->current_frame, 0, 0, cub, cub->main_menu_bg);
	if (cub->main_menu_bg->current_frame == 22)
		cub->main_menu_bg->current_frame = 0;
}

void	update_animation_start(t_cube *cub)
{

	if (cub->main_menu_start[cub->main_menu_start->current_frame].tmp_delay++ == cub->main_menu_start->delay)
	{
		cub->main_menu_start[cub->main_menu_start->current_frame].tmp_delay = 0;
		cub->main_menu_start->current_frame++;
	}
}

void	start_handler(t_cube *cub)
{
	update_animation_start(cub);
	draw_xpm_animation(cub->main_menu_start->current_frame, WIDTH / 2.2, HEIGHT / 1.1, cub, cub->main_menu_start);
	if (cub->main_menu_start->current_frame == 18)
		cub->main_menu_start->current_frame = 0;
}

void	update_animation_died(t_cube *cub)
{

	if (cub->game_over[cub->game_over->current_frame].tmp_delay++ == cub->game_over->delay)
	{
		cub->game_over[cub->game_over->current_frame].tmp_delay = 0;
		cub->game_over->current_frame++;
	}
}

void	died_handler(t_cube *cub)
{
	update_animation_died(cub);
	draw_xpm_animation(cub->game_over->current_frame, WIDTH / 2.8, HEIGHT / 3, cub, cub->game_over);
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

t_txt	enemy_animation_atk(t_cube *cub, t_txt *txt, t_enemy *enemy, int dist)
{
	(void) cub;
	update_animation_atk(txt);
	if (txt->current_frame == enemy->atk_max_frame)
	{
		txt->current_frame = 0;
		if (dist < 150)
			enemy->last_attack = 1;	
		enemy->attacking_bool = 0;
	}
	else
	{
		enemy->last_attack = 0;
		enemy->attacking_bool = 1;
	}
	return (txt[txt->current_frame]);
}

void	update_animation_hurt(t_txt *txt)
{

	if (txt[txt->current_frame].tmp_delay++ == txt->delay)
	{
		txt[txt->current_frame].tmp_delay = 0;
		txt->current_frame++;
	}
}

t_txt	enemy_animation_hurt(t_cube *cub, t_txt *txt, t_enemy *enemy, int max_frame)
{
	(void) cub;
	update_animation_hurt(txt);
	if (txt->current_frame == max_frame)
	{
		txt->current_frame = 0;
		enemy->hurt = 0;	
		enemy->attacking_bool = 0;
	}
	return (txt[txt->current_frame]);
}

void	update_animation_death(t_txt *txt)
{

	if (txt[txt->current_frame].tmp_delay++ == txt->delay)
	{
		txt[txt->current_frame].tmp_delay = 0;
		txt->current_frame++;
	}
}

t_txt	enemy_animation_death(t_cube *cub, t_txt *txt, t_enemy *enemy, int max_frame)
{
	(void) cub;
	update_animation_death(txt);
	if (txt->current_frame == max_frame)
	{
		enemy->dead = 1;	
		enemy->attacking_bool = 0;
		random_item(cub, &cub->dropped_items[cub->dropped_index]);
		cub->dropped_items[cub->dropped_index].x = enemy->x;
		cub->dropped_items[cub->dropped_index].y = enemy->y;
		cub->dropped_index++;
	}
	return (txt[txt->current_frame]);
}

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
	update_animation_general(txt);
	draw_xpm_animation(txt->current_frame, x, y, cub, txt);
	if (txt->current_frame == txt->frame_max)
		txt->current_frame = 0;
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
