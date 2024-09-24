/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_pickup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:01:00 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	crown_check(t_cube *cub, int i)
{
	cub->victory = 1;
	cub->level++;
	cub->items[i].display = 0;
}

void	check_items(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < cub->items_counter)
	{
		if (cub->items[i].display == 1 && cub->items[i].dist < 30)
		{
			if (cub->items[i].type == 'H' && cub->player.hp == 100)
			{
				cub->items[i].msg = 1;
				cub->items[i].last_text = get_current_time();
			}
			else if (cub->items[i].type == 'X')
				crown_check(cub, i);
			else
			{	
				cub->items[i].display = 0;
				cub->items[i].last_text = get_current_time();
				equip_item(cub, cub->items[i].type);
			}
		}
		i++;
	}
}

void	check_dropped(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < cub->dropped_index)
	{
		if (cub->dropped_items[i].display == 1
			&& cub->dropped_items[i].dist < 30)
		{
			if (cub->dropped_items[i].type == 'H' && cub->player.hp == 100)
			{
				cub->dropped_items[i].msg = 1;
				cub->dropped_items[i].last_text = get_current_time();
			}
			else
			{	
				cub->dropped_items[i].display = 0;
				cub->dropped_items[i].last_text = get_current_time();
				equip_item(cub, cub->dropped_items[i].type);
			}
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
		if (cub->weapons[i].display == 1 && cub->weapons[i].dist < 30)
		{
			cub->weapons[i].display = 0;
			cub->weapons[i].last_text = get_current_time();
			add_weapon_to_slot(cub, i);
		}
		i++;
	}
	check_items(cub);
	check_dropped(cub);
}
