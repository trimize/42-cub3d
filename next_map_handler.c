/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_map_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:42:21 by trimize           #+#    #+#             */
/*   Updated: 2024/07/16 16:40:24 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_enemies_items(t_cube *cub)
{
	cub->all_enemies = (t_enemy *)malloc
		(cub->enemy_counter * sizeof(t_enemy));
	cub->dropped_items = (t_item *)malloc
		(cub->enemy_counter * sizeof(t_item));
}

void	start_next_map(t_cube *cub)
{
	int		i;
	char	**file;

	i = 0;
	file = read_file(cub->path);
	(save_file(cub, file), map_filler(&cub->map), variables_checker(cub));
	if (first_and_last_checker(cub->map.map)
		|| space_checker_horizontal(cub->map.map)
		|| space_checker_vertical(cub->map.map))
		(printf("Error\nMap must be surrounded by walls.\n"),
			close_x(cub));
	while (cub->map.map[i])
		if (char_checker(cub->map.map[i++]))
			(printf("Error\nInvalid character on the map.\n"), close_x(cub));
	player_checker(cub);
	if (cub->weapon_counter > 0)
		cub->weapons = (t_item *)malloc(cub->weapon_counter * sizeof(t_item));
	if (cub->items_counter > 0)
		cub->items = (t_item *)malloc(cub->items_counter * sizeof(t_item));
	if (cub->door_counter > 0)
		cub->doors = (t_door *)malloc(cub->door_counter * sizeof(t_door));
	if (cub->enemy_counter > 0)
		init_enemies_items(cub);
	cub->start = 1;
	(load_textures(cub, cub->txt, 4), fill_player(cub), map_parsing(cub));
}

void	free_next_map(t_cube *cub)
{
	cub->fade_factor = 1;
	cub->victory = 0;
	(freetab(cub->map.map), free(cub->all_enemies), free(cub->dropped_items));
	(free(cub->weapons), free(cub->items), free(cub->doors));
	cub->map.map = NULL;
	free_stuff2(cub);
	cub->txt[0].path = NULL;
	cub->txt[0].type = NULL;
	cub->txt[1].path = NULL;
	cub->txt[1].type = NULL;
	cub->txt[2].path = NULL;
	cub->txt[2].type = NULL;
	cub->txt[3].path = NULL;
	cub->txt[3].type = NULL;
	cub->weapon_counter = 0;
	cub->items_counter = 0;
	cub->door_counter = 0;
	cub->enemy_counter = 0;
	(increment_numbers(&cub->path, cub->level), cub->dropped_index = 0);
	if (check_cub(cub->path))
		(printf("Error\nMap file must end in .cub\n"), close_x(cub));
}

void	next_map2(t_cube *cub)
{
	if ((cub->next_lvl_start) + cub->player_run_value >= cub->next_lvl_end)
	{
		animation_handler(cub->player_animations[0], cub,
			cub->next_lvl_start + cub->player_run_value, HEIGHT / 8);
		if (cub->idle_delay == 70)
			(free_next_map(cub), cub->idle_delay = 0, start_next_map(cub));
		else
			cub->idle_delay++;
	}
	else
		(animation_handler(cub->player_animations[1], cub,
				((cub->next_lvl_start) + cub->player_run_value),
				HEIGHT / 8), cub->player_run_value += 2);
	mlx_string_put(cub->con, cub->win, WIDTH / 4.55,
		HEIGHT / 2.8, 0xFFFFFF, "Forest");
	mlx_string_put(cub->con, cub->win, WIDTH / 2.07,
		HEIGHT / 2.8, 0xFFFFFF, "Cave");
	mlx_string_put(cub->con, cub->win, WIDTH / 1.37,
		HEIGHT / 2.8, 0xFFFFFF, "Catacombs");
}

void	next_map(t_cube *cub)
{
	cub->fade_factor -= 0.01;
	if (cub->fade_factor <= 0.0)
		cub->fade_factor = 0.0;
	fade_to_black(cub, cub->fade_factor, cub->bits_per_pixel);
	if (cub->fade_factor == 0.0)
	{
		if (cub->level == 2)
		{
			draw_xpm_animation(25, WIDTH / 4.8, HEIGHT / 3.8, cub->txt);
			cub->next_lvl_start = WIDTH / 5.2;
			cub->next_lvl_end = WIDTH / 2.23;
			next_map2(cub);
		}
		else if (cub->level == 3)
		{
			draw_xpm_animation(25, WIDTH / 4.8, HEIGHT / 3.8, cub->txt);
			cub->next_lvl_start = WIDTH / 2.23;
			cub->next_lvl_end = WIDTH / 1.413;
			next_map2(cub);
		}
		else
			(animation_handler(cub->victory_ani, cub, -60, HEIGHT / 8),
				animation_handler(cub->rat, cub, WIDTH / 4, HEIGHT / 2.5));
	}
}
