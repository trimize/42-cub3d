/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nightborne.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:17:20 by mbrandao          #+#    #+#             */
/*   Updated: 2024/07/14 21:40:28 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	save_txt(t_cube *cub, int i, int y, char *num)
{
	cub->nightborne[i][y].img = mlx_xpm_file_to_image
		(cub->con, num, &cub->nightborne[i][y].width,
			&cub->nightborne[i][y].height);
	cub->nightborne[i][y].addr = mlx_get_data_addr
		(cub->nightborne[i][y].img, &cub->nightborne[i][y].bits_per_pixel,
			&cub->nightborne[i][y].line_length,
			&cub->nightborne[i][y].endian);
	cub->nightborne[i][y].tmp_delay = 0;
}

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

		increment_numbers(num, y + 1);
		save_txt(cub, *i, y, num);
		y++;
	}
	free(num);
	cub->nightborne[*i]->delay = 8;
	cub->nightborne[*i]->current_frame = 0;
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
		increment_numbers(num, y + 1);
		save_txt(cub, *i, y, num);
		cub->nightborne[*i][y].tmp_delay = 0;
		y++;
	}
	cub->nightborne[*i]->delay = 8;
	cub->nightborne[*i]->current_frame = 0;
	free(num);
	(*i)++;
}

void	n_helper(char *num, int y)
{
	if (y == 9)
		(free(num), num = ft_strdup
			("./textures/Enemies/Nightborne/death/death10.xpm"));
	else if (y == 19)
		(free(num), num = ft_strdup
			("./textures/Enemies/Nightborne/death/death20.xpm"));
	else if (y >= 10 && y < 19)
		increment_numbers_2(num, y - 10 + 1);
	else if (y >= 20 && y < 29)
		increment_numbers_2(num, y - 20 + 1);
	else
		increment_numbers(num, y + 1);
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
		n_helper(num, y);
		save_txt(cub, i, y, num);
		cub->nightborne[i][y].tmp_delay = 0;
		y++;
	}
	cub->nightborne[i]->delay = 8;
	cub->nightborne[i]->current_frame = 0;
	free(num);
}
