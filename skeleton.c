/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeleton.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:02:54 by trimize           #+#    #+#             */
/*   Updated: 2024/07/15 16:55:31 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sk_idle(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	*i = 0;
	cub->skeleton[*i] = (t_txt *)malloc(11 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skeleton/idle/idle1.xpm");
	while (y < 11)
	{
		increment_numbers(&num, y + 1);
		cub->skeleton[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->skeleton[*i][y].width,
				&cub->skeleton[*i][y].height);
		cub->skeleton[*i][y].addr = mlx_get_data_addr
			(cub->skeleton[*i][y].img,
				&cub->skeleton[*i][y].bits_per_pixel,
				&cub->skeleton[*i][y].line_length,
				&cub->skeleton[*i][y].endian);
		cub->skeleton[*i][y++].tmp_delay = 0;
	}
	(free(num), cub->skeleton[*i]->delay = 8);
	(cub->skeleton[*i]->current_frame = 0, (*i)++);
}

void	sk_run(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->skeleton[*i] = (t_txt *)malloc(13 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skeleton/run/run1.xpm");
	while (y < 13)
	{

		increment_numbers(&num, y + 1);
		cub->skeleton[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->skeleton[*i][y].width,
				&cub->skeleton[*i][y].height);
		cub->skeleton[*i][y].addr = mlx_get_data_addr
			(cub->skeleton[*i][y].img,
				&cub->skeleton[*i][y].bits_per_pixel,
				&cub->skeleton[*i][y].line_length,
				&cub->skeleton[*i][y].endian);
		cub->skeleton[*i][y].tmp_delay = 0;
		y++;
	}
	cub->skeleton[*i]->delay = 2;
	cub->skeleton[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	sk_attack(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->skeleton[*i] = (t_txt *)malloc(18 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skeleton/attack/attack1.xpm");
	while (y < 18)
	{
		increment_numbers(&num, y + 1);
		cub->skeleton[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->skeleton[*i][y].width,
				&cub->skeleton[*i][y].height);
		cub->skeleton[*i][y].addr = mlx_get_data_addr
			(cub->skeleton[*i][y].img,
				&cub->skeleton[*i][y].bits_per_pixel,
				&cub->skeleton[*i][y].line_length,
				&cub->skeleton[*i][y].endian);
		cub->skeleton[*i][y].tmp_delay = 0;
		y++;
	}
	cub->skeleton[*i]->delay = 8;
	cub->skeleton[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	sk_hurt(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->skeleton[*i] = (t_txt *)malloc(8 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skeleton/hurt/hurt1.xpm");
	while (y < 8)
	{
		increment_numbers(&num, y + 1);
		cub->skeleton[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->skeleton[*i][y].width,
				&cub->skeleton[*i][y].height);
		cub->skeleton[*i][y].addr = mlx_get_data_addr
			(cub->skeleton[*i][y].img,
				&cub->skeleton[*i][y].bits_per_pixel,
				&cub->skeleton[*i][y].line_length,
				&cub->skeleton[*i][y].endian);
		cub->skeleton[*i][y].tmp_delay = 0;
		y++;
	}
	cub->skeleton[*i]->delay = 8;
	cub->skeleton[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	init_skeleton(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->skeleton = (t_txt **)malloc(5 * sizeof(t_txt *));
	(sk_idle(cub, &i), sk_run(cub, &i), sk_attack(cub, &i), sk_hurt(cub, &i));
	cub->skeleton[i] = (t_txt *)malloc(13 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/skeleton/death/death1.xpm");
	y = 0;
	while (y < 13)
	{
		increment_numbers(&num, y + 1);
		cub->skeleton[i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->skeleton[i][y].width,
				&cub->skeleton[i][y].height);
		cub->skeleton[i][y].addr = mlx_get_data_addr(cub->skeleton
			[i][y].img, &cub->skeleton[i][y].bits_per_pixel,
				&cub->skeleton[i][y].line_length,
				&cub->skeleton[i][y].endian);
		cub->skeleton[i][y].tmp_delay = 0;
		y++;
	}
	cub->skeleton[i]->delay = 8;
	cub->skeleton[i]->current_frame = 0;
	free(num);
}
