/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:01:58 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 15:07:27 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	map_parsing5(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 'v')
	{
		cub->all_enemies[mp->w].type = 'v';
		cub->all_enemies[mp->w].x = mp->x;
		cub->all_enemies[mp->w].y = mp->y;
		cub->all_enemies[mp->w].scale = 0.6;
		cub->all_enemies[mp->w].z_index = 80;
		cub->all_enemies[mp->w].atk_max_frame = 3;
		cub->all_enemies[mp->w].death_max_frame = 8;
		cub->all_enemies[mp->w].hurt_max_frame = 2;
		cub->all_enemies[mp->w].idle_max_frame = 5;
		cub->all_enemies[mp->w].run_max_frame = 7;
		cub->all_enemies[mp->w].attack_range = 100;
		cub->all_enemies[mp->w].attacking_bool = 0;
		cub->all_enemies[mp->w].last_attack = -1;
		cub->all_enemies[mp->w].dead = 0;
		cub->all_enemies[mp->w].hp = 100;
		cub->all_enemies[mp->w].hurt = 0;
		cub->all_enemies[mp->w].txt = cub->s_warrior[0][0];
		mp->w++;
	}
	else
		map_parsing6(cub, mp);
}

void	map_parsing4(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 's')
	{
		cub->all_enemies[mp->w].type = 's';
		cub->all_enemies[mp->w].x = mp->x;
		cub->all_enemies[mp->w].y = mp->y;
		cub->all_enemies[mp->w].scale = 0.8;
		cub->all_enemies[mp->w].z_index = 100;
		cub->all_enemies[mp->w].atk_max_frame = 17;
		cub->all_enemies[mp->w].death_max_frame = 12;
		cub->all_enemies[mp->w].hurt_max_frame = 7;
		cub->all_enemies[mp->w].idle_max_frame = 10;
		cub->all_enemies[mp->w].run_max_frame = 12;
		cub->all_enemies[mp->w].attack_range = 80;
		cub->all_enemies[mp->w].attacking_bool = 0;
		cub->all_enemies[mp->w].last_attack = -1;
		cub->all_enemies[mp->w].dead = 0;
		cub->all_enemies[mp->w].hp = 100;
		cub->all_enemies[mp->w].hurt = 0;
		cub->all_enemies[mp->w].txt = cub->skeleton[0][0];
		mp->w++;
	}
	else
		map_parsing5(cub, mp);
}

void	map_parsing3(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 'w')
	{
		cub->all_enemies[mp->w].type = 'w';
		cub->all_enemies[mp->w].x = mp->x;
		cub->all_enemies[mp->w].y = mp->y;
		cub->all_enemies[mp->w].scale = 0.4;
		cub->all_enemies[mp->w].z_index = 70;
		cub->all_enemies[mp->w].atk_max_frame = 6;
		cub->all_enemies[mp->w].death_max_frame = 6;
		cub->all_enemies[mp->w].hurt_max_frame = 2;
		cub->all_enemies[mp->w].idle_max_frame = 9;
		cub->all_enemies[mp->w].run_max_frame = 7;
		cub->all_enemies[mp->w].attack_range = 80;
		cub->all_enemies[mp->w].attacking_bool = 0;
		cub->all_enemies[mp->w].last_attack = -1;
		cub->all_enemies[mp->w].dead = 0;
		cub->all_enemies[mp->w].hp = 500;
		cub->all_enemies[mp->w].hurt = 0;
		cub->all_enemies[mp->w].txt = cub->warrior[0][0];
		mp->w++;
	}
	else
		map_parsing4(cub, mp);
}

void	map_parsing2(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 'k')
	{
		cub->all_enemies[mp->w].type = 'k';
		cub->all_enemies[mp->w].x = mp->x;
		cub->all_enemies[mp->w].y = mp->y;
		cub->all_enemies[mp->w].scale = 0.6;
		cub->all_enemies[mp->w].z_index = 40;
		cub->all_enemies[mp->w].atk_max_frame = 4;
		cub->all_enemies[mp->w].death_max_frame = 6;
		cub->all_enemies[mp->w].hurt_max_frame = 3;
		cub->all_enemies[mp->w].idle_max_frame = 5;
		cub->all_enemies[mp->w].run_max_frame = 4;
		cub->all_enemies[mp->w].attack_range = 80;
		cub->all_enemies[mp->w].attacking_bool = 0;
		cub->all_enemies[mp->w].last_attack = -1;
		cub->all_enemies[mp->w].dead = 0;
		cub->all_enemies[mp->w].hp = 100;
		cub->all_enemies[mp->w].hurt = 0;
		cub->all_enemies[mp->w].txt = cub->skullwolf[0][0];
		mp->w++;
	}
	else
		map_parsing3(cub, mp);
}

void	map_parsing(t_cube *cub)
{
	t_mparse	mp;

	mp.y = 0;
	mp.i = 0;
	mp.j = 0;
	mp.w = 0;
	mp.d = 0;
	while (cub->map.map[mp.y])
	{
		mp.x = 0;
		while (cub->map.map[mp.y][mp.x])
		{
			map_parsing2(cub, &mp);
			mp.x++;
		}
		mp.y++;
	}
}
