/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:25:27 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/15 17:49:10 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_cube	*call_cub(void)
{
	static t_cube	cub;

	return (&cub);
}

int	main(int argc, char **argv)
{
	t_cube	*cub;
	char	**file;

	cub = call_cub();
	cub->weapon_counter = 0;
	cub->items_counter = 0;
	cub->door_counter = 0;
	cub->enemy_counter = 0;
	cub->dropped_index = 0;
	cub->retry = 0;
	if (argc == 1)
	{
		cub->path = ft_strdup("./maps/map_1.cub");
		cub->level = 1;
	}
	else if (argc == 2)
	{
		cub->path = ft_strdup(argv[1]);
		cub->level = 0;
	}
	else
		(printf("Error\nInvalid number of arguments.\n"), exit(1));
	if (check_cub(cub->path))
		(printf("Error\nMap file must end in .cub\n"), free(cub->path), exit(1));
	file = read_file(cub->path);
	cub->txt = (t_txt *)malloc(26 * sizeof(t_txt));
	cub->rays = (t_raycast *) malloc ((WIDTH + 1) * sizeof(t_raycast));
	save_file(cub, file);
	player_checker(cub);
	map_filler(&cub->map);
	variables_checker(cub);
	if (first_and_last_checker(cub->map.map) || space_checker_horizontal(cub->map.map) || space_checker_vertical(cub->map.map))
		(printf("Error\nMap must be surrounded by walls.\n"), exit_free(cub)); // TODO Display better error message.
	int i = 0;
	while (cub->map.map[i])
		if (char_checker(cub->map.map[i++]))
			(printf("Error\nInvalid character on the map.\n"), exit_free(cub));
	if (cub->weapon_counter > 0)
		cub->weapons = (t_item *) malloc (cub->weapon_counter * sizeof(t_item));
	if (cub->items_counter > 0)
		cub->items = (t_item *) malloc (cub->items_counter * sizeof(t_item));
	if (cub->door_counter > 0)
		cub->doors = (t_door *) malloc (cub->door_counter * sizeof(t_door));
	if (cub->enemy_counter > 0)
	{
		cub->all_enemies = (t_enemy *) malloc (cub->enemy_counter * sizeof(t_enemy));
		cub->dropped_items = (t_item *) malloc (cub->enemy_counter * sizeof(t_item));
	}
	cub->start = 1;
	fill_player(cub);
	window_init(cub);
	// exit_free(&cub);
}

//int	main(int argc, char **argv)
//{
//	char	*str;

//	str = ft_strdup(argv[1]);
//	increment_numbers(&str, ft_atoi(argv[2]));
//	(void)argc;
//	printf("The path :             %s\nThe path incremented : %s", argv[1], str);
//	free(str);
//}
