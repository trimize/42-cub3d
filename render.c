/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:48:17 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/19 17:22:25 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_horizontal_line(t_cube *cub)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		((int *)(cub->addr))[(HEIGHT / 2) * (cub->line_length / 4) + i] = 0xFFFFFF;
		i++;;
	}
}

void	draw_vertical_line(t_cube *cub, double dist, int ray_i)
{
	int	i;
	int length;

	length = (int)( 9999 * (1 / dist));
	i = 0;
	while (i < length)
	{
		if (length > HEIGHT)
			length = HEIGHT;
		((int *)(cub->addr))[((HEIGHT / 2) + i - (length / 2)) * (cub->line_length / 4) + WIDTH - ray_i] = 0xFFFFFF;
		i++;
	}
}

void	render_3d(t_cube *cub, double dist, int ray_i)
{
	(void) cub;
	draw_horizontal_line(cub);
	draw_vertical_line(cub, dist, ray_i);
}
