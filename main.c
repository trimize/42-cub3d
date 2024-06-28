/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:25:27 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/28 17:37:52 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int mouse_clicked = 0;

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
	if (!cub) {
		printf("Memory allocation failed\n");
		return 0;
	}
	if (check_cub(path))
		(printf("Error\nMap file must end in .cub\n"), exit(1));
	file = read_file(path);
	cub->txt = (t_txt *)malloc(10 * sizeof(t_txt));
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
	cub->start = 1;
	fill_player(cub);
	window_init(cub);
	// exit_free(&cub);
}
