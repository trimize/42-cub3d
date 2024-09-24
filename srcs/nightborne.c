/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nightborne.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:17:20 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	n_idle(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	*i = 0;
	cub->nightborne[*i] = (t_txt *)malloc(9 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/idle/idle1.xpm");
	while (y < 9)
	{
		increment_numbers(&num, y + 1);
		cub->nightborne[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->nightborne[*i][y].width,
				&cub->nightborne[*i][y].height);
		cub->nightborne[*i][y].addr = mlx_get_data_addr
			(cub->nightborne[*i][y].img, &cub->nightborne[*i][y].bits_per_pixel,
				&cub->nightborne[*i][y].line_length,
				&cub->nightborne[*i][y].endian);
		cub->nightborne[*i][y].tmp_delay = 0;
		y++;
	}
	free(num);
	cub->nightborne[*i]->delay = 8;
	cub->nightborne[*i]->current_frame = 0;
	cub->nightborne[(*i)++]->frame_max = 8;
}

void	n_run(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->nightborne[*i] = (t_txt *)malloc(6 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/run/run1.xpm");
	while (y < 6)
	{
		increment_numbers(&num, y + 1);
		cub->nightborne[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->nightborne[*i][y].width,
				&cub->nightborne[*i][y].height);
		cub->nightborne[*i][y].addr = mlx_get_data_addr
			(cub->nightborne[*i][y].img, &cub->nightborne[*i][y].bits_per_pixel,
				&cub->nightborne[*i][y].line_length,
				&cub->nightborne[*i][y].endian);
		cub->nightborne[*i][y].tmp_delay = 0;
		y++;
	}
	cub->nightborne[*i]->delay = 8;
	cub->nightborne[*i]->current_frame = 0;
	cub->nightborne[*i]->frame_max = 5;
	free(num);
	(*i)++;
}

void	n_attack(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->nightborne[*i] = (t_txt *)malloc(12 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/attack/attack1.xpm");
	while (y < 12)
	{
		increment_numbers(&num, y + 1);
		cub->nightborne[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->nightborne[*i][y].width,
				&cub->nightborne[*i][y].height);
		cub->nightborne[*i][y].addr = mlx_get_data_addr
			(cub->nightborne[*i][y].img, &cub->nightborne[*i][y].bits_per_pixel,
				&cub->nightborne[*i][y].line_length,
				&cub->nightborne[*i][y].endian);
		cub->nightborne[*i][y].tmp_delay = 0;
		y++;
	}
	cub->nightborne[*i]->delay = 8;
	cub->nightborne[*i]->current_frame = 0;
	cub->nightborne[*i]->frame_max = 11;
	free(num);
	(*i)++;
}

void	n_hurt(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->nightborne[*i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/hurt/hurt1.xpm");
	while (y < 5)
	{
		increment_numbers(&num, y + 1);
		cub->nightborne[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->nightborne[*i][y].width,
				&cub->nightborne[*i][y].height);
		cub->nightborne[*i][y].addr = mlx_get_data_addr
			(cub->nightborne[*i][y].img, &cub->nightborne[*i][y].bits_per_pixel,
				&cub->nightborne[*i][y].line_length,
				&cub->nightborne[*i][y].endian);
		cub->nightborne[*i][y].tmp_delay = 0;
		y++;
	}
	cub->nightborne[*i]->delay = 8;
	cub->nightborne[*i]->current_frame = 0;
	cub->nightborne[*i]->frame_max = 4;
	free(num);
	(*i)++;
}

void	init_nightborne(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->nightborne = (t_txt **)malloc(5 * sizeof(t_txt *));
	(n_idle(cub, &i), n_run(cub, &i), n_attack(cub, &i), n_hurt(cub, &i));
	cub->nightborne[i] = (t_txt *)malloc(22 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/Nightborne/death/death1.xpm");
	y = 0;
	while (y < 22)
	{
		increment_numbers(&num, y + 1);
		cub->nightborne[i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->nightborne[i][y].width,
				&cub->nightborne[i][y].height);
		cub->nightborne[i][y].addr = mlx_get_data_addr
			(cub->nightborne[i][y].img, &cub->nightborne[i][y].bits_per_pixel,
				&cub->nightborne[i][y].line_length,
				&cub->nightborne[i][y].endian);
		cub->nightborne[i][y].tmp_delay = 0;
		y++;
	}
	cub->nightborne[i]->delay = 8;
	cub->nightborne[i]->current_frame = 0;
	(free(num), cub->nightborne[i]->frame_max = 21);
}
