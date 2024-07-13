/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:09:33 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/13 17:53:58 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_xpm_alpha(int alpha, int x, int y, t_cube *cub)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (i < cub->abc[alpha].height)
	{
		while (j < cub->abc[alpha].width)
		{
			if (((int *)(cub->abc[alpha].addr))[(i)
				* cub->abc[alpha].line_length / 4 + j] == 0xFFFFFF)
				((int *)(cub->addr))[(y + i) * cub->line_length / 4
					+ x + j] = ((int *)(cub->abc[alpha].addr))[(i)
					* cub->abc[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_xpm_texture2(t_draw *draw)
{
	t_cube	*cub;

	cub = call_cub();
	if (draw->alpha == 7 || draw->alpha == 8 || draw->alpha == 9
		|| draw->alpha == 11 || draw->alpha == 12 || draw->alpha == 13
		|| draw->alpha == 14 || draw->alpha == 15
		|| draw->alpha == 16 || draw->alpha == 17 || draw->alpha == 18)
	{
		if (draw->x + draw->j < WIDTH && draw->y + draw->i < HEIGHT && ((int *)
				(cub->txt[draw->alpha].addr))[(draw->i)
			* cub->txt[draw->alpha].line_length / 4 + draw->j] != 0x0000FF)
			((int *)(cub->addr))[(draw->y + draw->i) * cub->line_length
				/ 4 + draw->x + draw->j] = ((int *)(cub->txt[draw->alpha].addr))
			[(draw->i) * cub->txt[draw->alpha].line_length / 4 + draw->j];
	}
	else
		((int *)(cub->addr))[(draw->y + draw->i) * cub->line_length / 4
			+ draw->x + draw->j] = ((int *)(cub->txt[draw->alpha].addr))
		[(draw->i) * cub->txt[draw->alpha].line_length / 4 + draw->j];
}

void	draw_xpm_texture(int alpha, int x, int y, t_cube *cub)
{
	t_draw	draw;

	draw.alpha = alpha;
	draw.x = x;
	draw.y = y;
	draw.i = 0;
	while (draw.i < cub->txt[alpha].height)
	{
		draw.j = 0;
		while (draw.j < cub->txt[alpha].width)
		{
			if (alpha == 5 || alpha == 6)
			{
				if (((int *)(cub->txt[alpha].addr))[(draw.i)
					* cub->txt[alpha].line_length / 4 + draw.j] == 0xFFFFFF)
					((int *)(cub->addr))[(y + draw.i) * cub->line_length
						/ 4 + x + draw.j] = ((int *)(cub->txt[alpha].addr))
					[(draw.i) * cub->txt[alpha].line_length / 4 + draw.j];
			}
			else
				draw_xpm_texture2(&draw);
			draw.j++;
		}
		draw.i++;
	}
}

void	draw_xpm_hp(int alpha, int x, int y, t_cube *cub)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (i < cub->hp_frame[alpha].height)
	{
		while (j < cub->hp_frame[alpha].width)
		{
			((int *)(cub->addr))[(y + i) * cub->line_length
				/ 4 + x + j] = ((int *)(cub->hp_frame[alpha].addr))[(i)
				* cub->hp_frame[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_xpm_number(int alpha, int x, int y, t_cube *cub)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (i < cub->nums[alpha].height)
	{
		while (j < cub->nums[alpha].width)
		{
			if (((int *)(cub->nums[alpha].addr))[(i)
				* cub->nums[alpha].line_length / 4 + j] == 0xFFFFFF)
				((int *)(cub->addr))[(y + i) * cub->line_length
					/ 4 + x + j] = ((int *)(cub->nums[alpha].addr))[(i)
					* cub->nums[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
	}
}
