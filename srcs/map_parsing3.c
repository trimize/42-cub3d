/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:27:12 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_parsing13(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 'D')
	{
		cub->doors[mp->d].is_open = 0;
		cub->doors[mp->d].y = mp->y;
		cub->doors[mp->d].x = mp->x;
		cub->doors[mp->d].is_closing = 0;
		cub->doors[mp->d].txt = cub->door;
		cub->doors[mp->d].frame = 0;
		mp->d++;
	}
	else if (cub->map.map[mp->y][mp->x] == '|')
	{
		cub->weapons[mp->i].txt = &cub->txt[9];
		cub->weapons[mp->i].x = mp->x;
		cub->weapons[mp->i].y = mp->y;
		cub->weapons[mp->i].type = '|';
		cub->weapons[mp->i].display = 1;
		mp->i++;
	}
}

void	map_parsing12(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 'O')
	{
		cub->weapons[mp->i].txt = &cub->txt[13];
		cub->weapons[mp->i].x = mp->x;
		cub->weapons[mp->i].y = mp->y;
		cub->weapons[mp->i].type = 'O';
		cub->weapons[mp->i].display = 1;
		mp->i++;
	}
	else if (cub->map.map[mp->y][mp->x] == 'C')
	{
		cub->weapons[mp->i].txt = &cub->txt[11];
		cub->weapons[mp->i].x = mp->x;
		cub->weapons[mp->i].y = mp->y;
		cub->weapons[mp->i].type = 'C';
		cub->weapons[mp->i].display = 1;
		mp->i++;
	}
	else
		map_parsing13(cub, mp);
}

void	map_parsing11(t_cube *cub, t_mparse *mp)
{
	if (cub->map.map[mp->y][mp->x] == 'G')
	{
		cub->weapons[mp->i].txt = &cub->txt[14];
		cub->weapons[mp->i].x = mp->x;
		cub->weapons[mp->i].y = mp->y;
		cub->weapons[mp->i].type = 'G';
		cub->weapons[mp->i].display = 1;
		mp->i++;
	}
	else if (cub->map.map[mp->y][mp->x] == 'Q')
	{
		cub->items[mp->j].txt = &cub->txt[17];
		cub->items[mp->j].x = mp->x;
		cub->items[mp->j].y = mp->y;
		cub->items[mp->j].type = 'Q';
		cub->items[mp->j].display = 1;
		mp->j++;
	}
	else
		map_parsing12(cub, mp);
}
