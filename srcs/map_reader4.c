/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:39:06 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 16:39:23 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	variables_checker(t_cube *cub)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (!ft_equalstr(cub->txt[i].type, "NO")
			&& !ft_equalstr(cub->txt[i].type, "SO")
			&& !ft_equalstr(cub->txt[i].type, "WE")
			&& !ft_equalstr(cub->txt[i].type, "EA"))
		{
			printf("Error\nInvalid variables on the map.\n");
			if (cub->level > 1)
				close_x(cub);
			free_stuff(cub);
			free(cub->path);
			free(cub->txt);
			freetab(cub->map.map);
			exit(1);
		}
		i++;
	}
}
