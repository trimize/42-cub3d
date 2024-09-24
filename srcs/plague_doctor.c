/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plague_doctor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:07:51 by mbrandao          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pd_idle(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	*i = 0;
	cub->plague_doctor[*i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/plague_doctor/idle/idle1.xpm");
	while (y < 4)
	{
		increment_numbers(&num, y + 1);
		cub->plague_doctor[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->plague_doctor[*i][y].width,
				&cub->plague_doctor[*i][y].height);
		cub->plague_doctor[*i][y].addr = mlx_get_data_addr
			(cub->plague_doctor[*i][y].img,
				&cub->plague_doctor[*i][y].bits_per_pixel,
				&cub->plague_doctor[*i][y].line_length,
				&cub->plague_doctor[*i][y].endian);
		cub->plague_doctor[*i][y].tmp_delay = 0;
		y++;
	}
	cub->plague_doctor[*i]->delay = 20;
	cub->plague_doctor[*i]->current_frame = 0;
	(free(num), cub->plague_doctor[*i]->frame_max = 3);
	(*i)++;
}

void	pd_run(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->plague_doctor[*i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/plague_doctor/run/run1.xpm");
	while (y < 4)
	{
		increment_numbers(&num, y + 1);
		cub->plague_doctor[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->plague_doctor[*i][y].width,
				&cub->plague_doctor[*i][y].height);
		cub->plague_doctor[*i][y].addr = mlx_get_data_addr
			(cub->plague_doctor[*i][y].img,
				&cub->plague_doctor[*i][y].bits_per_pixel,
				&cub->plague_doctor[*i][y].line_length,
				&cub->plague_doctor[*i][y].endian);
		cub->plague_doctor[*i][y].tmp_delay = 0;
		y++;
	}
	cub->plague_doctor[*i]->delay = 10;
	cub->plague_doctor[*i]->current_frame = 0;
	(free(num), cub->plague_doctor[*i]->frame_max = 3);
	(*i)++;
}

void	pd_attack(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->plague_doctor[*i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/plague_doctor/attack/attack1.xpm");
	while (y < 5)
	{
		increment_numbers(&num, y + 1);
		cub->plague_doctor[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->plague_doctor[*i][y].width,
				&cub->plague_doctor[*i][y].height);
		cub->plague_doctor[*i][y].addr = mlx_get_data_addr
			(cub->plague_doctor[*i][y].img,
				&cub->plague_doctor[*i][y].bits_per_pixel,
				&cub->plague_doctor[*i][y].line_length,
				&cub->plague_doctor[*i][y].endian);
		cub->plague_doctor[*i][y].tmp_delay = 0;
		y++;
	}
	cub->plague_doctor[*i]->delay = 20;
	cub->plague_doctor[*i]->current_frame = 0;
	cub->plague_doctor[*i]->frame_max = 4;
	free(num);
	(*i)++;
}

void	pd_hurt(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->plague_doctor[*i] = (t_txt *)malloc(3 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/plague_doctor/hurt/hurt1.xpm");
	while (y < 3)
	{
		increment_numbers(&num, y + 1);
		cub->plague_doctor[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->plague_doctor[*i][y].width,
				&cub->plague_doctor[*i][y].height);
		cub->plague_doctor[*i][y].addr = mlx_get_data_addr
			(cub->plague_doctor[*i][y].img,
				&cub->plague_doctor[*i][y].bits_per_pixel,
				&cub->plague_doctor[*i][y].line_length,
				&cub->plague_doctor[*i][y].endian);
		cub->plague_doctor[*i][y].tmp_delay = 0;
		y++;
	}
	cub->plague_doctor[*i]->delay = 12;
	cub->plague_doctor[*i]->current_frame = 0;
	cub->plague_doctor[*i]->frame_max = 2;
	free(num);
	(*i)++;
}

void	init_plague_doctor(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->plague_doctor = (t_txt **)malloc(5 * sizeof(t_txt *));
	(pd_idle(cub, &i), pd_run(cub, &i), pd_attack(cub, &i), pd_hurt(cub, &i));
	cub->plague_doctor[i] = (t_txt *)malloc(6 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/plague_doctor/death/death1.xpm");
	y = 0;
	while (y < 6)
	{
		increment_numbers(&num, y + 1);
		cub->plague_doctor[i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->plague_doctor[i][y].width,
				&cub->plague_doctor[i][y].height);
		cub->plague_doctor[i][y].addr = mlx_get_data_addr(cub->plague_doctor
			[i][y].img, &cub->plague_doctor[i][y].bits_per_pixel,
				&cub->plague_doctor[i][y].line_length,
				&cub->plague_doctor[i][y].endian);
		cub->plague_doctor[i][y].tmp_delay = 0;
		y++;
	}
	cub->plague_doctor[i]->delay = 8;
	cub->plague_doctor[i]->current_frame = 0;
	(free(num), cub->plague_doctor[i]->frame_max = 5);
}
