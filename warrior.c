/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warrior.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:02:54 by trimize           #+#    #+#             */
/*   Updated: 2024/07/16 16:47:34 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	w_idle(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	*i = 0;
	cub->warrior[*i] = (t_txt *)malloc(10 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/warrior/idle/idle1.xpm");
	while (y < 10)
	{
		increment_numbers(&num, y + 1);
		cub->warrior[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->warrior[*i][y].width,
				&cub->warrior[*i][y].height);
		cub->warrior[*i][y].addr = mlx_get_data_addr
			(cub->warrior[*i][y].img,
				&cub->warrior[*i][y].bits_per_pixel,
				&cub->warrior[*i][y].line_length,
				&cub->warrior[*i][y].endian);
		cub->warrior[*i][y++].tmp_delay = 0;
	}
	(free(num), cub->warrior[*i]->delay = 8);
	cub->warrior[*i]->frame_max = 9;
	cub->warrior[*i]->current_frame = 0;
	(*i)++;
}

void	w_run(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->warrior[*i] = (t_txt *)malloc(8 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/warrior/run/run1.xpm");
	while (y < 8)
	{
		increment_numbers(&num, y + 1);
		cub->warrior[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->warrior[*i][y].width,
				&cub->warrior[*i][y].height);
		cub->warrior[*i][y].addr = mlx_get_data_addr
			(cub->warrior[*i][y].img,
				&cub->warrior[*i][y].bits_per_pixel,
				&cub->warrior[*i][y].line_length,
				&cub->warrior[*i][y].endian);
		cub->warrior[*i][y].tmp_delay = 0;
		y++;
	}
	cub->warrior[*i]->delay = 10;
	cub->warrior[*i]->current_frame = 0;
	cub->warrior[(*i)++]->frame_max = 7;
	free(num);
}

void	w_attack(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->warrior[*i] = (t_txt *)malloc(7 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/warrior/attack/attack1.xpm");
	while (y < 7)
	{
		increment_numbers(&num, y + 1);
		cub->warrior[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->warrior[*i][y].width,
				&cub->warrior[*i][y].height);
		cub->warrior[*i][y].addr = mlx_get_data_addr
			(cub->warrior[*i][y].img,
				&cub->warrior[*i][y].bits_per_pixel,
				&cub->warrior[*i][y].line_length,
				&cub->warrior[*i][y].endian);
		cub->warrior[*i][y].tmp_delay = 0;
		y++;
	}
	cub->warrior[*i]->delay = 14;
	cub->warrior[*i]->current_frame = 0;
	cub->warrior[*i]->frame_max = 6;
	free(num);
	(*i)++;
}

void	w_hurt(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->warrior[*i] = (t_txt *)malloc(3 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/warrior/hurt/hurt1.xpm");
	while (y < 3)
	{
		increment_numbers(&num, y + 1);
		cub->warrior[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->warrior[*i][y].width,
				&cub->warrior[*i][y].height);
		cub->warrior[*i][y].addr = mlx_get_data_addr
			(cub->warrior[*i][y].img,
				&cub->warrior[*i][y].bits_per_pixel,
				&cub->warrior[*i][y].line_length,
				&cub->warrior[*i][y].endian);
		cub->warrior[*i][y].tmp_delay = 0;
		y++;
	}
	cub->warrior[*i]->delay = 12;
	cub->warrior[*i]->current_frame = 0;
	cub->warrior[*i]->frame_max = 2;
	free(num);
	(*i)++;
}

void	init_warrior(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->warrior = (t_txt **)malloc(5 * sizeof(t_txt *));
	(w_idle(cub, &i), w_run(cub, &i), w_attack(cub, &i), w_hurt(cub, &i));
	cub->warrior[i] = (t_txt *)malloc(7 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/warrior/death/death1.xpm");
	y = 0;
	while (y < 7)
	{
		increment_numbers(&num, y + 1);
		cub->warrior[i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->warrior[i][y].width,
				&cub->warrior[i][y].height);
		cub->warrior[i][y].addr = mlx_get_data_addr(cub->warrior
			[i][y].img, &cub->warrior[i][y].bits_per_pixel,
				&cub->warrior[i][y].line_length,
				&cub->warrior[i][y].endian);
		cub->warrior[i][y].tmp_delay = 0;
		y++;
	}
	cub->warrior[i]->delay = 8;
	cub->warrior[i]->current_frame = 0;
	(free(num), cub->warrior[i]->frame_max = 6);
}
