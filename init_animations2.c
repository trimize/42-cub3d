/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:10:28 by trimize           #+#    #+#             */
/*   Updated: 2024/07/15 18:12:01 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_explosion(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->explosion = (t_txt *)malloc(14 * sizeof(t_txt));
	num = ft_strdup("./textures/explosion_animation/explosion1.xpm");
	while (i < 9)
	{
		increment_numbers(&num, i + 1);
		cub->explosion[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->explosion[i].width,
				&cub->explosion[i].height);
		cub->explosion[i].addr = mlx_get_data_addr
			(cub->explosion[i].img, &cub->explosion[i].bits_per_pixel,
				&cub->explosion[i].line_length, &cub->explosion[i].endian);
		cub->explosion[i].tmp_delay = 0;
		i++;
	}
	cub->explosion->delay = 7;
	cub->explosion->current_frame = 0;
	free(num);
}

void	init_dragon(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->dragon = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/dragon_animation/dragon1.xpm");
	while (i < 5)
	{
		increment_numbers(&num, i + 1);
		cub->dragon[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->dragon[i].width, &cub->dragon[i].height);
		cub->dragon[i].addr = mlx_get_data_addr
			(cub->dragon[i].img, &cub->dragon[i].bits_per_pixel,
				&cub->dragon[i].line_length, &cub->dragon[i].endian);
		cub->dragon[i].tmp_delay = 0;
		i++;
	}
	cub->dragon->delay = 15;
	cub->dragon->current_frame = 0;
	free(num);
}

void	init_crossbow(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->crossbow = (t_txt *)malloc(6 * sizeof(t_txt));
	num = ft_strdup("./textures/crossbow_animation/crossbow1.xpm");
	while (i < 6)
	{
		increment_numbers(&num, i + 1);
		cub->crossbow[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->crossbow[i].width, &cub->crossbow[i].height);
		cub->crossbow[i].addr = mlx_get_data_addr
			(cub->crossbow[i].img, &cub->crossbow[i].bits_per_pixel,
				&cub->crossbow[i].line_length, &cub->crossbow[i].endian);
		cub->crossbow[i].tmp_delay = 0;
		i++;
	}
	cub->crossbow->delay = 18;
	cub->crossbow->current_frame = 0;
	free(num);
}

void	init_hp(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	num = ft_strdup("./textures/hp/hp1.xpm");
	cub->hp_frame = (t_txt *)malloc(8 * sizeof(t_txt));
	while (i < 8)
	{
		increment_numbers(&num, i + 1);
		cub->hp_frame[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->hp_frame[i].width, &cub->hp_frame[i].height);
		cub->hp_frame[i].addr = mlx_get_data_addr
			(cub->hp_frame[i].img, &cub->hp_frame[i].bits_per_pixel,
				&cub->hp_frame[i].line_length, &cub->hp_frame[i].endian);
		cub->hp_frame[i].tmp_delay = 0;
		i++;
	}
	cub->hp_frame->delay = 6;
	cub->hp_frame->current_frame = 1;
	free(num);
}

void	init_sword(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	cub->sword_ani = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/sword_animation/sword1.xpm");
	while (i < 5)
	{
		increment_numbers(&num, i + 1);
		cub->sword_ani[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->sword_ani[i].width,
				&cub->sword_ani[i].height);
		cub->sword_ani[i].addr = mlx_get_data_addr
			(cub->sword_ani[i].img, &cub->sword_ani[i].bits_per_pixel,
				&cub->sword_ani[i].line_length, &cub->sword_ani[i].endian);
		cub->sword_ani[i].tmp_delay = 0;
		i++;
	}
	cub->sword_ani->current_frame = 0;
	cub->sword_ani->delay = 10;
	free(num);
}
