/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:50:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	close_x_helper(t_cube *cub)
{
	printf("You closed the game.");
	free_txt(cub);
	if (cub->map.map)
		freetab(cub->map.map);
	free(cub->path);
	free_imgs(cub, cub->abc, 26);
	free_imgs(cub, cub->nums, 10);
	free_imgs(cub, cub->sword_ani, 5);
	free_imgs(cub, cub->hp_frame, 8);
	free_imgs(cub, cub->crossbow, 6);
	free_imgs(cub, cub->dragon, 5);
	free_imgs(cub, cub->explosion, 13);
	free_imgs(cub, cub->title_screen, 29);
	free_imgs(cub, cub->main_menu_bg, 24);
	free_imgs(cub, cub->main_menu_start, 19);
	free_imgs(cub, cub->game_over, 11);
	free_imgs(cub, cub->keyboard, 12);
	free_imgs(cub, cub->door, 7);
	free_imgs(cub, cub->crown, 8);
	free_imgs(cub, cub->rat, 66);
	free_imgs(cub, cub->victory_ani, 3);
	mlx_destroy_image(cub->con, cub->main_menu_assets->img);
	(free(cub->main_menu_assets->path), free(cub->main_menu_assets));
	free_animations(cub, cub->nightborne, 5);
	free_animations(cub, cub->skeleton, 5);
}

int	close_x(t_cube *cub)
{
	close_x_helper(cub);
	free_animations(cub, cub->warrior, 5);
	free_animations(cub, cub->skullwolf, 5);
	free_animations(cub, cub->s_warrior, 5);
	free_animations(cub, cub->plague_doctor, 5);
	free_animations(cub, cub->cute_wolf, 5);
	free_animations(cub, cub->player_animations, 2);
	if (cub->weapon_counter)
		free(cub->weapons);
	if (cub->enemy_counter)
	{
		free(cub->all_enemies);
		free(cub->dropped_items);
	}
	if (cub->items_counter)
		free(cub->items);
	if (cub->door_counter)
		free(cub->doors);
	free(cub->rays);
	mlx_destroy_window(cub->con, cub->win);
	mlx_destroy_display(cub->con);
	free(cub->con);
	exit(0);
	return (0);
}

void	player_movement_rotation(t_cube *cub)
{
	if (cub->player.hp > 0 && !cub->victory)
	{
		player_movement(cub);
		if (cub->start == 1)
			player_rotation_init(cub);
		if (cub->option_bool == -1)
			mouse_rotate(cub);
		if (cub->key.left && cub->option_bool == -1)
			rotate_player(cub, (cub->p_rotation));
		if (cub->key.right && cub->option_bool == -1)
			rotate_player(cub, -(cub->p_rotation));
	}
}

void	loop_hook_helper(t_cube *cub)
{
	int	i;

	player_movement_rotation(cub);
	(update_dist(cub), check_pick_up(cub), put_enemies(cub));
	(render_game(cub), check_door(cub), sword_handler(cub));
	(hp_handler(cub), crossbow_handler(cub), shield_handler(cub));
	(weapon_slot_handler(cub), dragon_handler(cub), explosion_sprite(cub));
	i = 0;
	while (i < cub->items_counter)
	{
		if (cub->items[i].type == 'X' && cub->items[i].display == 1)
			cub->items[i].txt = crown_handler(cub->crown);
		i++;
	}
	draw_xpm_texture(15, WIDTH / 1.08, HEIGHT / 6, cub);
	draw_xpm_texture(16, WIDTH / 1.08, HEIGHT / 10, cub);
	draw_xpm_texture(17, WIDTH / 1.069, HEIGHT / 22, cub);
	if (cub->start == 1)
		player_rotation_init(cub);
	if (cub->option_bool == -1)
		mouse_rotate(cub);
	if (cub->key.left && cub->option_bool == -1)
		rotate_player(cub, (cub->p_rotation));
	if (cub->key.right && cub->option_bool == -1)
		rotate_player(cub, -(cub->p_rotation));
}

void	window_init(t_cube *cub)
{
	cub->con = mlx_init();
	if (cub->con == NULL)
		(printf("Error\nCouldn't start minilibx.\n"), exit_free(cub));
	cub->win = mlx_new_window(cub->con, WIDTH, HEIGHT, "cub3d");
	if (cub->win == NULL)
		(mlx_destroy_display(cub->con), free(cub->con),
			printf("Error\nCouldn't open the window.\n"), exit_free(cub));
	(init_textures(cub), load_textures(cub, cub->txt, 26), init_alphabet(cub));
	(init_hp(cub), init_crossbow(cub), init_dragon(cub));
	(init_explosion(cub), init_title(cub), init_main_menu_bg(cub));
	(init_main_menu_start(cub), init_game_over(cub), init_keyboard(cub));
	(init_nightborne(cub), init_skeleton(cub), init_warrior(cub));
	(init_skullwolf(cub), init_s_warrior(cub), init_plague_doctor(cub));
	(init_cute_wolf(cub), init_door(cub), init_crown(cub));
	(init_player_animations(cub), map_parsing(cub));
	(init_main_menu_a(cub), init_rat(cub), init_victory_ani(cub));
	(load_textures(cub, cub->main_menu_assets, 1), init_numbers(cub));
	(mlx_mouse_hide(cub->con, cub->win), init_sword(cub));
	(start_keys(cub), mlx_key_hook(cub->win, handle_key_release, cub));
	mlx_hook(cub->win, KeyPress, KeyPressMask, handle_key_press, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, handle_key_release, cub);
	mlx_hook(cub->win, ButtonPress, ButtonPressMask, mouse_events, 0);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask,
		close_x, cub);
	(mlx_loop_hook(cub->con, loop_hook, cub), mlx_loop(cub->con));
}
