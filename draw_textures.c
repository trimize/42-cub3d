/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:09:33 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/28 18:10:02 by mbrandao         ###   ########.fr       */
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
			if (((int *)(cub->abc[alpha].addr))[(i) * cub->abc[alpha].line_length / 4 + j] == 0xFFFFFF)
				((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->abc[alpha].addr))[(i) * cub->abc[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_xpm_s_animation(int alpha, int x, int y, t_cube *cub)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (i < cub->sword_ani[alpha].height)
	{
		while (j < cub->sword_ani[alpha].width)
		{
			if (x + j < WIDTH && y + i < HEIGHT && ((int *)(cub->sword_ani[alpha].addr))[(i) * cub->sword_ani[alpha].line_length / 4 + j] != 0x0000FF)
					((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->sword_ani[alpha].addr))[(i) * cub->sword_ani[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_xpm_texture(int alpha, int x, int y, t_cube *cub)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (i < cub->txt[alpha].height)
	{
		while (j < cub->txt[alpha].width)
		{
			if (alpha == 5 || alpha == 6)
			{
				if (((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j] == 0xFFFFFF)
					((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j];
			}
			else if (alpha == 7 || alpha == 8 || alpha == 9)
			{
				if (((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j] != 0x0000FF)
					((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j];
			}
			else
				((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->txt[alpha].addr))[(i) * cub->txt[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
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
			((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->hp_frame[alpha].addr))[(i) * cub->hp_frame[alpha].line_length / 4 + j];
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
			if (((int *)(cub->nums[alpha].addr))[(i) * cub->nums[alpha].line_length / 4 + j] == 0xFFFFFF)	
				((int *)(cub->addr))[(y + i) * cub->line_length / 4 + x + j] = ((int *)(cub->nums[alpha].addr))[(i) * cub->nums[alpha].line_length / 4 + j];
			j++;
		}
		j = 0;
		i++;
	}
}
