/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:25:27 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/08 20:20:44 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(void)
{
	t_cube	cub;
	char	*path = "maps/map.cub";
	char	**file;

	file = read_file(path);
	save_file(&cub, file);
	map_filler(&cub.map);
	variables_checker(&cub);
	if (first_and_last_checker(cub.map.map) || space_checker_horizontal(cub.map.map) || space_checker_vertical(cub.map.map))
		(printf("Map must be surrounded by walls.\n"), exit_free(&cub)); // TODO Display better error message.
	int i = 0;
	while (cub.map.map[i])
		if (char_checker(cub.map.map[i++]))
			(printf("Invalid character on the map.\n"), exit_free(&cub));
}
