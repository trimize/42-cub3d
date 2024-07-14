/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cute_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:50:15 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/14 21:03:58 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	cw_idle(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	*i = 0;
	cub->cute_wolf[*i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/cute_wolf/idle/idle1.xpm");
	while (y < 4)
	{
		increment_numbers(num, y + 1);
		cub->cute_wolf[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->cute_wolf[*i][y].width,
				&cub->cute_wolf[*i][y].height);
		cub->cute_wolf[*i][y].addr = mlx_get_data_addr
			(cub->cute_wolf[*i][y].img, &cub->cute_wolf[*i][y].bits_per_pixel,
				&cub->cute_wolf[*i][y].line_length,
				&cub->cute_wolf[*i][y].endian);
		cub->cute_wolf[*i][y].tmp_delay = 0;
		y++;
	}
	cub->cute_wolf[*i]->delay = 20;
	cub->cute_wolf[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	cw_run(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->cute_wolf[*i] = (t_txt *)malloc(4 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/cute_wolf/run/run1.xpm");
	while (y < 4)
	{

		increment_numbers(num, y + 1);
		cub->cute_wolf[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->cute_wolf[*i][y].width,
				&cub->cute_wolf[*i][y].height);
		cub->cute_wolf[*i][y].addr = mlx_get_data_addr
			(cub->cute_wolf[*i][y].img, &cub->cute_wolf[*i][y].bits_per_pixel,
				&cub->cute_wolf[*i][y].line_length,
				&cub->cute_wolf[*i][y].endian);
		cub->cute_wolf[*i][y].tmp_delay = 0;
		y++;
	}
	cub->cute_wolf[*i]->delay = 10;
	cub->cute_wolf[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	cw_attack(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->cute_wolf[*i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/cute_wolf/attack/attack1.xpm");
	while (y < 5)
	{
		increment_numbers(num, y + 1);
		cub->cute_wolf[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->cute_wolf[*i][y].width,
				&cub->cute_wolf[*i][y].height);
		cub->cute_wolf[*i][y].addr = mlx_get_data_addr
			(cub->cute_wolf[*i][y].img, &cub->cute_wolf[*i][y].bits_per_pixel,
				&cub->cute_wolf[*i][y].line_length,
				&cub->cute_wolf[*i][y].endian);
		cub->cute_wolf[*i][y].tmp_delay = 0;
		y++;
	}
	cub->cute_wolf[*i]->delay = 20;
	cub->cute_wolf[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	cw_hurt(t_cube *cub, int *i)
{
	int		y;
	char	*num;

	y = 0;
	cub->cute_wolf[*i] = (t_txt *)malloc(3 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/cute_wolf/hurt/hurt1.xpm");
	while (y < 3)
	{
		increment_numbers(num, y + 1);
		cub->cute_wolf[*i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->cute_wolf[*i][y].width,
				&cub->cute_wolf[*i][y].height);
		cub->cute_wolf[*i][y].addr = mlx_get_data_addr
			(cub->cute_wolf[*i][y].img, &cub->cute_wolf[*i][y].bits_per_pixel,
				&cub->cute_wolf[*i][y].line_length,
				&cub->cute_wolf[*i][y].endian);
		cub->cute_wolf[*i][y].tmp_delay = 0;
		y++;
	}
	cub->cute_wolf[*i]->delay = 12;
	cub->cute_wolf[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	init_cute_wolf(t_cube *cub)
{
	int		i;
	int		y;
	char	*num;

	cub->cute_wolf = (t_txt **)malloc(5 * sizeof(t_txt *));
	(cw_idle(cub, &i), cw_run(cub, &i), cw_attack(cub, &i), cw_hurt(cub, &i));
	cub->cute_wolf[i] = (t_txt *)malloc(5 * sizeof(t_txt));
	num = ft_strdup("./textures/Enemies/cute_wolf/death/death1.xpm");
	y = 0;
	while (y < 5)
	{
		increment_numbers(num, y + 1);
		cub->cute_wolf[i][y].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->cute_wolf[i][y].width,
				&cub->cute_wolf[i][y].height);
		cub->cute_wolf[i][y].addr = mlx_get_data_addr
			(cub->cute_wolf[i][y].img, &cub->cute_wolf[i][y].bits_per_pixel,
				&cub->cute_wolf[i][y].line_length,
				&cub->cute_wolf[i][y].endian);
		cub->cute_wolf[i][y].tmp_delay = 0;
		y++;
	}
	cub->cute_wolf[i]->delay = 8;
	cub->cute_wolf[i]->current_frame = 0;
	free(num);
}
