/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skullwolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:02:54 by trimize           #+#    #+#             */
/*   Updated: 2024/07/15 16:55:31 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	skw_idle(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	*i = 0;
	cub->skullwolf[*i] = (t_txt *)malloc(6 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skullwolf/idle/idle1.xpm");
	while (y < 6)
	{
		increment_numbers(&num, y + 1);
		cub->skullwolf[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->skullwolf[*i][y].width,
				&cub->skullwolf[*i][y].height);
		cub->skullwolf[*i][y].addr = mlx_get_data_addr
			(cub->skullwolf[*i][y].img,
				&cub->skullwolf[*i][y].bits_per_pixel,
				&cub->skullwolf[*i][y].line_length,
				&cub->skullwolf[*i][y].endian);
		cub->skullwolf[*i][y].tmp_delay = 0;
		y++;
	}
	free(num);
	cub->skullwolf[*i]->delay = 8;
	cub->skullwolf[*i]->current_frame = 0;
	(*i)++;
}

void	skw_run(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->skullwolf[*i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skullwolf/run/run1.xpm");
	while (y < 5)
	{

		increment_numbers(&num, y + 1);
		cub->skullwolf[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->skullwolf[*i][y].width,
				&cub->skullwolf[*i][y].height);
		cub->skullwolf[*i][y].addr = mlx_get_data_addr
			(cub->skullwolf[*i][y].img,
				&cub->skullwolf[*i][y].bits_per_pixel,
				&cub->skullwolf[*i][y].line_length,
				&cub->skullwolf[*i][y].endian);
		cub->skullwolf[*i][y].tmp_delay = 0;
		y++;
	}
	cub->skullwolf[*i]->delay = 10;
	cub->skullwolf[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	skw_attack(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->skullwolf[*i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skullwolf/attack/attack1.xpm");
	while (y < 5)
	{
		increment_numbers(&num, y + 1);
		cub->skullwolf[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->skullwolf[*i][y].width,
				&cub->skullwolf[*i][y].height);
		cub->skullwolf[*i][y].addr = mlx_get_data_addr
			(cub->skullwolf[*i][y].img,
				&cub->skullwolf[*i][y].bits_per_pixel,
				&cub->skullwolf[*i][y].line_length,
				&cub->skullwolf[*i][y].endian);
		cub->skullwolf[*i][y].tmp_delay = 0;
		y++;
	}
	cub->skullwolf[*i]->delay = 10;
	cub->skullwolf[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	skw_hurt(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->skullwolf[*i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skullwolf/hurt/hurt1.xpm");
	while (y < 4)
	{
		increment_numbers(&num, y + 1);
		cub->skullwolf[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->skullwolf[*i][y].width,
				&cub->skullwolf[*i][y].height);
		cub->skullwolf[*i][y].addr = mlx_get_data_addr
			(cub->skullwolf[*i][y].img,
				&cub->skullwolf[*i][y].bits_per_pixel,
				&cub->skullwolf[*i][y].line_length,
				&cub->skullwolf[*i][y].endian);
		cub->skullwolf[*i][y].tmp_delay = 0;
		y++;
	}
	cub->skullwolf[*i]->delay = 12;
	cub->skullwolf[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	init_skullwolf(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->skullwolf = (t_txt **)malloc(5 * sizeof(t_txt *));
	(skw_idle(cub, &i), skw_run(cub, &i), skw_attack(cub, &i), skw_hurt(cub, &i));
	cub->skullwolf[i] = (t_txt *)malloc(7 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skullwolf/death/death1.xpm");
	y = 0;
	while (y < 7)
	{
		increment_numbers(&num, y + 1);
		cub->skullwolf[i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->skullwolf[i][y].width,
				&cub->skullwolf[i][y].height);
		cub->skullwolf[i][y].addr = mlx_get_data_addr(cub->skullwolf
			[i][y].img, &cub->skullwolf[i][y].bits_per_pixel,
				&cub->skullwolf[i][y].line_length,
				&cub->skullwolf[i][y].endian);
		cub->skullwolf[i][y].tmp_delay = 0;
		y++;
	}
	cub->skullwolf[i]->delay = 8;
	cub->skullwolf[i]->current_frame = 0;
	free(num);
}
