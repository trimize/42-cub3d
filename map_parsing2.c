/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:26:43 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/13 18:26:52 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	map_parsing10(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 'A')
	{
		cub->items[mp->j].txt = &cub->txt[16];
		cub->items[mp->j].x = mp->x;
		cub->items[mp->j].y = mp->y;
		cub->items[mp->j].type = 'A';
		cub->items[mp->j].display = 1;
		mp->j++;
	}
	else if (cub->map.map[mp->y][mp->x] == 'H')
	{
		cub->items[mp->j].txt = &cub->txt[22];
		cub->items[mp->j].x = mp->x;
		cub->items[mp->j].y = mp->y;
		cub->items[mp->j].type = 'H';
		cub->items[mp->j].display = 1;
		cub->items[mp->j].msg = 0;
		cub->items[mp->j].last_text = -1;
		mp->j++;
	}
	else
		map_parsing11(cub, mp);
}

void	map_parsing9(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 'R')
	{
		cub->items[mp->j].x = mp->x;
		cub->items[mp->j].y = mp->y;
		random_item(cub, &cub->items[mp->j++]);
	}
	else if (cub->map.map[mp->y][mp->x] == 'X')
	{
		cub->items[mp->j].txt = &cub->crown[cub->crown->current_frame];
		cub->items[mp->j].x = mp->x;
		cub->items[mp->j].y = mp->y;
		cub->items[mp->j].type = 'X';
		cub->items[mp->j++].display = 1;
	}
	else if (cub->map.map[mp->y][mp->x] == 'V')
	{
		cub->items[mp->j].txt = &cub->txt[15];
		cub->items[mp->j].x = mp->x;
		cub->items[mp->j].y = mp->y;
		cub->items[mp->j].type = 'V';
		cub->items[mp->j++].display = 1;
	}
	else
		map_parsing10(cub, mp);
}

void	map_parsing8(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 'n')
	{
		cub->all_enemies[mp->w].type = 'n';
		cub->all_enemies[mp->w].x = mp->x;
		cub->all_enemies[mp->w].y = mp->y;
		cub->all_enemies[mp->w].scale = 0.4;
		cub->all_enemies[mp->w].z_index = 20;
		cub->all_enemies[mp->w].atk_max_frame = 11;
		cub->all_enemies[mp->w].death_max_frame = 21;
		cub->all_enemies[mp->w].hurt_max_frame = 4;
		cub->all_enemies[mp->w].idle_max_frame = 8;
		cub->all_enemies[mp->w].run_max_frame = 5;
		cub->all_enemies[mp->w].attack_range = 150;
		cub->all_enemies[mp->w].attacking_bool = 0;
		cub->all_enemies[mp->w].last_attack = -1;
		cub->all_enemies[mp->w].dead = 0;
		cub->all_enemies[mp->w].hp = 500;
		cub->all_enemies[mp->w].hurt = 0;
		cub->all_enemies[mp->w].txt = cub->nightborne[0][0];
		mp->w++;
	}
	else
		map_parsing9(cub, mp);
}

void	map_parsing7(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 'c')
	{
		cub->all_enemies[mp->w].type = 'c';
		cub->all_enemies[mp->w].x = mp->x;
		cub->all_enemies[mp->w].y = mp->y;
		cub->all_enemies[mp->w].scale = 0.6;
		cub->all_enemies[mp->w].z_index = 80;
		cub->all_enemies[mp->w].atk_max_frame = 4;
		cub->all_enemies[mp->w].death_max_frame = 4;
		cub->all_enemies[mp->w].hurt_max_frame = 2;
		cub->all_enemies[mp->w].idle_max_frame = 3;
		cub->all_enemies[mp->w].run_max_frame = 3;
		cub->all_enemies[mp->w].attack_range = 70;
		cub->all_enemies[mp->w].attacking_bool = 0;
		cub->all_enemies[mp->w].last_attack = -1;
		cub->all_enemies[mp->w].dead = 0;
		cub->all_enemies[mp->w].hp = 100;
		cub->all_enemies[mp->w].hurt = 0;
		cub->all_enemies[mp->w].txt = cub->cute_wolf[0][0];
		mp->w++;
	}
	else
		map_parsing8(cub, mp);
}

void	map_parsing6(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 'p')
	{
		cub->all_enemies[mp->w].type = 'p';
		cub->all_enemies[mp->w].x = mp->x;
		cub->all_enemies[mp->w].y = mp->y;
		cub->all_enemies[mp->w].scale = 0.6;
		cub->all_enemies[mp->w].z_index = 80;
		cub->all_enemies[mp->w].atk_max_frame = 4;
		cub->all_enemies[mp->w].death_max_frame = 5;
		cub->all_enemies[mp->w].hurt_max_frame = 2;
		cub->all_enemies[mp->w].idle_max_frame = 3;
		cub->all_enemies[mp->w].run_max_frame = 3;
		cub->all_enemies[mp->w].attack_range = 70;
		cub->all_enemies[mp->w].attacking_bool = 0;
		cub->all_enemies[mp->w].last_attack = -1;
		cub->all_enemies[mp->w].dead = 0;
		cub->all_enemies[mp->w].hp = 500;
		cub->all_enemies[mp->w].hurt = 0;
		cub->all_enemies[mp->w].txt = cub->plague_doctor[0][0];
		mp->w++;
	}
	else
		map_parsing7(cub, mp);
}
