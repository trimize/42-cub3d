/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner_dealer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:46:13 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	remove_corners(t_cube *cub, int x, int y)
{
	if (cub->map.map[y + 1][x] == '2')
		cub->map.map[y + 1][x] = '0';
	else if (cub->map.map[y - 1][x] == '2')
		cub->map.map[y - 1][x] = '0';
	else if (cub->map.map[y][x + 1] == '2')
		cub->map.map[y][x + 1] = '0';
	else if (cub->map.map[y][x - 1] == '2')
		cub->map.map[y][x - 1] = '0';
	return (1);
}

int	is_corner(t_cube *cub, int x, int y)
{
	if ((cub->map.map[y - 1][x + 1] == '0' || cub->map.map[y - 1][x + 1] == ' ')
		&& cub->map.map[y][x + 1] == '1' && cub->map.map[y - 1][x] == '1')
		(cub->map.map[y - 1][x + 1] = '2');
	else if ((cub->map.map[y - 1][x - 1] == '0' || cub->map.map[y - 1]
		[x - 1] == ' ') && cub->map.map[y][x - 1] == '1'
			&& cub->map.map[y - 1][x] == '1')
		(cub->map.map[y - 1][x - 1] = '2');
	else if ((cub->map.map[y + 1][x - 1] == '0' || cub->map.map[y + 1]
		[x - 1] == ' ') && cub->map.map[y][x - 1] == '1'
			&& cub->map.map[y + 1][x] == '1')
		(cub->map.map[y + 1][x - 1] = '2');
	else if ((cub->map.map[y + 1][x + 1] == '0' || cub->map.map[y + 1]
		[x + 1] == ' ') && cub->map.map[y + 1][x] == '1'
			&& cub->map.map[y][x + 1] == '1')
		cub->map.map[y + 1][x + 1] = '2';
	return (1);
}
