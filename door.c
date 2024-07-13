/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:51:29 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/13 14:33:22 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_door	*search_door(t_cube *cub, int x, int y)
{
	int	i;

	i = 0;
	while(i < cub->door_counter)
	{
		if (x == cub->doors[i].x && y == cub->doors[i].y)
			return (&cub->doors[i]);
		i++;
	}
	return (NULL);
}

void	check_door(t_cube *cub)
{
	t_raycast ray;

	ray = cub->rays[WIDTH / 2];
	// printf("%f\n", ray.d_dist);
	if (ray.is_door && !ray.door->is_open && ray.d_dist < 120 && !ray.door->is_closing)
	{
		cub->door_open_msg = 1;
		if (cub->key.e)
		{
			ray.door->txt = txt_handler(cub, cub->door, 6, ray);
		}
	}
	else if (ray.is_door && (ray.door->is_open || ray.door->is_closing) && ray.d_dist < 120)
	{
		cub->door_close_msg = 1;
		if (cub->key.e)
		{
			ray.door->txt = txt_handler_r(cub, cub->door, ray);
		}
	}
	else
	{
		cub->door_open_msg = 0;
		cub->door_close_msg = 0;
		cub->key.e = 0;
	}
}

int	can_walk(t_cube *cub, int y, int x)
{
	if (cub->map.map[y][x] == 'D' && search_door(cub, x, y)->is_open == 0)
		return (0);
	return (1);
}
