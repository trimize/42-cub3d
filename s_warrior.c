/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_warrior.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:57:17 by trimize           #+#    #+#             */
/*   Updated: 2024/07/15 16:55:31 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sw_idle(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	*i = 0;
	cub->s_warrior[*i] = (t_txt *)malloc(6 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/s_warrior/idle/idle1.xpm");
	while (y < 6)
	{
		increment_numbers(&num, y + 1);
		cub->s_warrior[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->s_warrior[*i][y].width,
				&cub->s_warrior[*i][y].height);
		cub->s_warrior[*i][y].addr = mlx_get_data_addr
			(cub->s_warrior[*i][y].img,
				&cub->s_warrior[*i][y].bits_per_pixel,
				&cub->s_warrior[*i][y].line_length,
				&cub->s_warrior[*i][y].endian);
		cub->s_warrior[*i][y].tmp_delay = 0;
		y++;
	}
	free(num);
	cub->s_warrior[*i]->delay = 20;
	cub->s_warrior[*i]->current_frame = 0;
	(*i)++;
}

void	sw_run(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->s_warrior[*i] = (t_txt *)malloc(8 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/s_warrior/run/run1.xpm");
	while (y < 8)
	{

		increment_numbers(&num, y + 1);
		cub->s_warrior[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->s_warrior[*i][y].width,
				&cub->s_warrior[*i][y].height);
		cub->s_warrior[*i][y].addr = mlx_get_data_addr
			(cub->s_warrior[*i][y].img,
				&cub->s_warrior[*i][y].bits_per_pixel,
				&cub->s_warrior[*i][y].line_length,
				&cub->s_warrior[*i][y].endian);
		cub->s_warrior[*i][y].tmp_delay = 0;
		y++;
	}
	cub->s_warrior[*i]->delay = 10;
	cub->s_warrior[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	sw_attack(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->s_warrior[*i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/s_warrior/attack/attack1.xpm");
	while (y < 4)
	{
		increment_numbers(&num, y + 1);
		cub->s_warrior[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->s_warrior[*i][y].width,
				&cub->s_warrior[*i][y].height);
		cub->s_warrior[*i][y].addr = mlx_get_data_addr
			(cub->s_warrior[*i][y].img,
				&cub->s_warrior[*i][y].bits_per_pixel,
				&cub->s_warrior[*i][y].line_length,
				&cub->s_warrior[*i][y].endian);
		cub->s_warrior[*i][y].tmp_delay = 0;
		y++;
	}
	cub->s_warrior[*i]->delay = 20;
	cub->s_warrior[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	sw_hurt(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->s_warrior[*i] = (t_txt *)malloc(3 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/s_warrior/hurt/hurt1.xpm");
	while (y < 3)
	{
		increment_numbers(&num, y + 1);
		cub->s_warrior[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->s_warrior[*i][y].width,
				&cub->s_warrior[*i][y].height);
		cub->s_warrior[*i][y].addr = mlx_get_data_addr
			(cub->s_warrior[*i][y].img,
				&cub->s_warrior[*i][y].bits_per_pixel,
				&cub->s_warrior[*i][y].line_length,
				&cub->s_warrior[*i][y].endian);
		cub->s_warrior[*i][y].tmp_delay = 0;
		y++;
	}
	cub->s_warrior[*i]->delay = 12;
	cub->s_warrior[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	init_s_warrior(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->s_warrior = (t_txt **)malloc(5 * sizeof(t_txt *));
	(sw_idle(cub, &i), sw_run(cub, &i), sw_attack(cub, &i), sw_hurt(cub, &i));
	cub->s_warrior[i] = (t_txt *)malloc(9 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/s_warrior/death/death1.xpm");
	y = 0;
	while (y < 9)
	{
		increment_numbers(&num, y + 1);
		cub->s_warrior[i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->s_warrior[i][y].width,
				&cub->s_warrior[i][y].height);
		cub->s_warrior[i][y].addr = mlx_get_data_addr(cub->s_warrior
			[i][y].img, &cub->s_warrior[i][y].bits_per_pixel,
				&cub->s_warrior[i][y].line_length,
				&cub->s_warrior[i][y].endian);
		cub->s_warrior[i][y].tmp_delay = 0;
		y++;
	}
	cub->s_warrior[i]->delay = 8;
	cub->s_warrior[i]->current_frame = 0;
	free(num);
}
