/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:25:27 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/11 14:46:57 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_cube	*call_cub(void)
{
	static t_cube	cub;

	return (&cub);
}

int	main(void)
{
	t_cube	*cub;
	char	*path = "maps/map.cub";
	char	**file;

	cub = call_cub();
	cub->casket_x = 2;
	cub->casket_y = 2;
	cub->weapon_counter = 0;
	cub->items_counter = 0;
	cub->retry = 0;
	if (check_cub(path))
		(printf("Error\nMap file must end in .cub\n"), exit(1));
	file = read_file(path);
	cub->txt = (t_txt *)malloc(20 * sizeof(t_txt));
	cub->rays = (t_raycast *)malloc((WIDTH + 1) * sizeof(t_raycast));
	save_file(cub, file);
	player_checker(cub);
	if (cub->weapon_counter > 0)
		cub->weapons = (t_item *) malloc(cub->weapon_counter * sizeof(t_item));
	map_filler(&cub->map);
	variables_checker(cub);
	if (first_and_last_checker(cub->map.map) || space_checker_horizontal(cub->map.map) || space_checker_vertical(cub->map.map))
		(printf("Error\nMap must be surrounded by walls.\n"), exit_free(cub)); // TODO Display better error message.
	int i = 0;
	while (cub->map.map[i])
		if (char_checker(cub->map.map[i++]))
			(printf("Error\nInvalid character on the map.\n"), exit_free(cub));
	cub->start = 1;
	fill_player(cub);
	window_init(cub);
	// exit_free(&cub);
}
