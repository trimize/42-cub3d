/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:50:02 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/15 20:31:34 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	close_x(t_cube *cub)
{
	printf("You closed the game.");
	int	i = 0;
	while (i < 4)
		mlx_destroy_image(cub->con, cub->txt[i++].img);
	mlx_destroy_window(cub->con, cub->win);
	mlx_destroy_display(cub->con);
	free(cub->con);
	// free_map(data->map);
	exit_free(cub);
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

int	loop_hook(t_cube *cub)
{
	void	*img;

	img = mlx_new_image(cub->con, WIDTH, HEIGHT);
	cub->img = img;
	cub->addr = mlx_get_data_addr
		(img, &cub->bits_per_pixel, &cub->line_length, &cub->endian);
	if (cub->title_bool == 0 && cub->bg_bool == 0)
		loop_hook_helper(cub);
	if (cub->title_bool == 1 && !cub->victory)
		title_handler(cub);
	if (cub->bg_bool && !cub->victory)
		bg_true(cub);
	(mlx_put_image_to_window(cub->con, cub->win, cub->img, 0, 0), display_messages(cub));
	if (!cub->title_bool && !cub->bg_bool
		&& !cub->victory && cub->minimap_bool == 1)
		(draw_map_to_image(cub), draw_player_to_image(cub));
	if (cub->title_bool == 0 && cub->bg_bool == 0 && !cub->victory)
		hud_options_handler(cub);
	if (cub->player.hp <= 0 && !cub->bg_bool && !cub->victory)
		dying_handler(cub);
	else if (cub->player.hp > 0 && !cub->bg_bool && cub->victory)
		next_map(cub);
	if (cub->tuto && !cub->title_bool && !cub->bg_bool && !cub->victory)
		tutorial(cub, cub->bits_per_pixel);
	return (mlx_destroy_image(cub->con, img), 0);
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
	(init_alphabet(cub), init_numbers(cub), init_sword(cub));
	(init_hp(cub), init_crossbow(cub), init_dragon(cub));
	(init_explosion(cub), init_title(cub), init_main_menu_bg(cub));
	(init_main_menu_start(cub), init_game_over(cub), init_keyboard(cub));
	(init_nightborne(cub), init_skeleton(cub), init_warrior(cub));
	(init_skullwolf(cub), init_s_warrior(cub), init_plague_doctor(cub));
	(init_cute_wolf(cub), init_door(cub), init_crown(cub));
	(init_player_animations(cub), map_parsing(cub));
	init_main_menu_a(cub);
	(load_textures(cub, cub->main_menu_assets, 1), init_textures(cub));
	(mlx_mouse_hide(cub->con, cub->win), load_textures(cub, cub->txt, 26));
	(start_keys(cub), mlx_key_hook(cub->win, handle_key_release, cub));
	mlx_hook(cub->win, KeyPress, KeyPressMask, handle_key_press, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, handle_key_release, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask,
		close_x, cub);
	mlx_hook(cub->win, ButtonPress, ButtonPressMask, mouse_events, 0);
	(mlx_loop_hook(cub->con, loop_hook, cub), mlx_loop(cub->con));
}
