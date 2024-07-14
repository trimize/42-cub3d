/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:28:09 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/14 20:28:36 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_square_to_image(t_cube *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
			((int *)(cub->addr))[(y + i)
				* cub->line_length / 4 + x + j++] = color;
		i++;
	}
}

void	draw_p_to_image(t_cube *cub, int x, int y, int color)
{
	int	i;
	int	j;

	if (x < 0 || y < 0 || x + PLAYER_SIZE >= cub->line_length / 4
		|| y + PLAYER_SIZE >= cub->line_length / 4)
		return ;
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
			((int *)(cub->addr))[(y + i)
				* cub->line_length / 4 + x + j++] = color;
		i++;
	}
}

void	draw_player_to_image(t_cube *cub)
{
	int	x;
	int	y;
	int	color;

	color = 0xFF0000;
	x = cub->player.x * MINIMAP_SIZE;
	y = cub->player.y * MINIMAP_SIZE;
	draw_p_to_image(cub, x, y, color);
}

void	draw_map_to_image(t_cube *cub)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < cub->map.rows)
	{
		x = 0;
		while (x < cub->map.cols)
		{
			if (cub->map.map[y][x] == '1')
				color = 0x00004A;
			else if (cub->map.map[y][x] == ' ')
				continue ;
			else
				color = 0xffece0;
			draw_square_to_image(cub, x * MINIMAP_SIZE,
				y * MINIMAP_SIZE, color);
			x++;
		}
		y++;
	}
}
