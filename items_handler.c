/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 01:01:20 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/04 01:29:23 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	update_dist(t_cube *cub)
{
	int	i;

	i = -1;
	while (++i < cub->weapon_counter)
		cub->weapons[i].dist = dist(cub->weapons[i].x, cub->weapons[i].y, cub->player.x, cub->player.y);
}

void	add_weapon_to_slot(t_cube *cub, int index)
{
	int	i;
	int	type;

	i = 0;
	if (cub->weapons[index].type == '|')
		type = 1;
	else if (cub->weapons[index].type == 'C')
		type = 2;
	else if (cub->weapons[index].type == 'O')
		type = 3;
	else if (cub->weapons[index].type == 'G')
		type = 4;
	while (i < 4)
	{
		if (cub->weapons_in_slot[i] == 0)
		{
			cub->weapons_in_slot[i] = type;
			return ;
		}
		i++;
	}
}

void	check_pick_up(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < cub->weapon_counter)
	{
		if (cub->weapons[i].display == 1 && cub->weapons[i].dist < 1)
		{
			cub->weapons[i].display = 0;
			cub->weapons[i].last_text = get_current_time();
			add_weapon_to_slot(cub, i);
		}
		i++;
	}
}
