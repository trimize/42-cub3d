/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:44:48 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_xpm_animation(int alpha, int x, int y, t_txt *txt)
{
	t_cube	*cub;
	int		i;
	int		j;
	int		color;

	cub = call_cub();
	i = 0;
	while (i < txt[alpha].height)
	{
		j = 0;
		while (j < txt[alpha].width)
		{
			color = *(int *)(txt[alpha].addr + (i * txt[alpha].line_length
						+ j * txt[alpha].bits_per_pixel / 8));
			if (x + j < WIDTH && y + i < HEIGHT && color != 0x0000FF)
				((int *)(cub->addr))[(y + i) * cub->line_length / 4
					+ x + j] = color;
			j++;
		}
		i++;
	}
}
