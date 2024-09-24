/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_cutscene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:57:17 by trimize           #+#    #+#             */
/*   Updated: 2024/07/16 16:51:38 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pla_idle(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	*i = 0;
	cub->player_animations[*i] = (t_txt *)malloc(10 * sizeof(t_txt));
	num = ft_strdup("./textures/player/idle/idle1.xpm");
	while (y < 10)
	{
		increment_numbers(&num, y + 1);
		cub->player_animations[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->player_animations[*i][y].width,
				&cub->player_animations[*i][y].height);
		cub->player_animations[*i][y].addr = mlx_get_data_addr
			(cub->player_animations[*i][y].img,
				&cub->player_animations[*i][y].bits_per_pixel,
				&cub->player_animations[*i][y].line_length,
				&cub->player_animations[*i][y].endian);
		cub->player_animations[*i][y++].tmp_delay = 0;
	}
	free(num);
	cub->player_animations[*i]->delay = 10;
	cub->player_animations[*i]->current_frame = 0;
	cub->player_animations[*i]->frame_max = 9;
	(*i)++;
}

void	pla_run(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->player_animations[*i] = (t_txt *)malloc(10 * sizeof(t_txt));
	num = ft_strdup("./textures/player/run/run1.xpm");
	while (y < 10)
	{
		increment_numbers(&num, y + 1);
		cub->player_animations[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->player_animations[*i][y].width,
				&cub->player_animations[*i][y].height);
		cub->player_animations[*i][y].addr = mlx_get_data_addr
			(cub->player_animations[*i][y].img,
				&cub->player_animations[*i][y].bits_per_pixel,
				&cub->player_animations[*i][y].line_length,
				&cub->player_animations[*i][y].endian);
		cub->player_animations[*i][y].tmp_delay = 0;
		y++;
	}
	cub->player_animations[*i]->delay = 10;
	cub->player_animations[*i]->current_frame = 0;
	cub->player_animations[*i]->frame_max = 9;
	free(num);
}

void	init_player_animations(t_cube *cub)
{
	int		i;

	cub->player_animations = (t_txt **)malloc(2 * sizeof(t_txt *));
	(pla_idle(cub, &i), pla_run(cub, &i));
}
