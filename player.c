/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:47:26 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/08 21:49:13 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	fill_player(t_cube *cub)
{
	char		**map;
	int			i;
	int			j;

	i = 0;
	j = 0;
	map = cub->map.map;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N')
			{
				cub->player.y = i;
				cub->player.x = j;
				cub->player.dir = 0;
				return ;
			}
			else if (map[i][j] == 'E')
			{
				cub->player.y = i;
				cub->player.x = j;
				cub->player.dir = 1;
				return ;
			}
			else if (map[i][j] == 'S')
			{
				cub->player.y = i;
				cub->player.x = j;
				cub->player.dir = 2;
				return ;
			}
			else if (map[i][j] == 'W')
			{
				cub->player.y = i;
				cub->player.x = j;
				cub->player.dir = 3;
				return ;
			}
			j++;
		}
		i++;
	}
}
