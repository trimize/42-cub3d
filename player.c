/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:47:26 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/13 16:10:07 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	fill_player_2(t_cube *cub, char	**map, int i, int j)
{
	if (map[i][j] == 'E')
	{
		cub->player.y = i;
		cub->player.x = j;
		cub->player.dir = 1;
		return (1);
	}
	else if (map[i][j] == 'S')
	{
		cub->player.y = i;
		cub->player.x = j;
		cub->player.dir = 2;
		return (1);
	}
	else if (map[i][j] == 'W')
	{
		cub->player.y = i;
		cub->player.x = j;
		cub->player.dir = 3;
		return (1);
	}
	return (0);
}

void	fill_player(t_cube *cub)
{
	char		**map;
	int			i;
	int			j;

	i = 0;
	map = cub->map.map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N')
			{
				cub->player.y = i;
				cub->player.x = j;
				cub->player.dir = 0;
				return ;
			}
			else if (fill_player_2(cub, map, i, j))
				return ;
			j++;
		}
		i++;
	}
}
