/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   victory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:51:03 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/16 16:51:08 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_rat(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	num = ft_strdup("./textures/rat_animation/rat1.xpm");
	cub->rat = (t_txt *)malloc(66 * sizeof(t_txt));
	while (i < 66)
	{
		increment_numbers(&num, i + 1);
		cub->rat[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->rat[i].width, &cub->rat[i].height);
		cub->rat[i].addr = mlx_get_data_addr
			(cub->rat[i].img, &cub->rat[i].bits_per_pixel,
				&cub->rat[i].line_length, &cub->rat[i].endian);
		cub->rat[i].tmp_delay = 0;
		i++;
	}
	cub->rat->delay = 2;
	cub->rat->current_frame = 0;
	cub->rat->frame_max = 65;
	free(num);
}

void	init_victory_ani(t_cube *cub)
{
	int		i;
	char	*num;

	i = 0;
	num = ft_strdup("./textures/victory_animation/victory1.xpm");
	cub->victory_ani = (t_txt *)malloc(3 * sizeof(t_txt));
	while (i < 3)
	{
		increment_numbers(&num, i + 1);
		cub->victory_ani[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->victory_ani[i].width,
				&cub->victory_ani[i].height);
		cub->victory_ani[i].addr = mlx_get_data_addr
			(cub->victory_ani[i].img, &cub->victory_ani[i].bits_per_pixel,
				&cub->victory_ani[i].line_length, &cub->victory_ani[i].endian);
		cub->victory_ani[i].tmp_delay = 0;
		i++;
	}
	cub->victory_ani->delay = 6;
	cub->victory_ani->current_frame = 1;
	cub->victory_ani->frame_max = 2;
	free(num);
}
