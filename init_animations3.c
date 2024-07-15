/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animations3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:13:46 by trimize           #+#    #+#             */
/*   Updated: 2024/07/15 18:23:57 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_numbers(t_cube *cub)
{
	int		i;
	int		x;
	int		y;
	char	*num;

	i = 0;
	cub->nums = (t_txt *)malloc(10 * sizeof(t_txt));
	num = ft_strdup("./textures/numbers/0.xpm");
	while (i < 10)
	{
		cub->nums[i].img = mlx_xpm_file_to_image(cub->con, num, &x, &y);
		cub->nums[i].addr = mlx_get_data_addr
			(cub->nums[i].img, &cub->nums[i].bits_per_pixel,
				&cub->nums[i].line_length, &cub->nums[i].endian);
		cub->nums[i].width = 22;
		cub->nums[i].height = 34;
		i++;
		increment_numbers(&num, i);
	}
	free(num);
}

void	init_door(t_cube *cub)
{
	int		i;
	char	*num;

	cub->door = (t_txt *)malloc(7 * sizeof(t_txt));
	i = 0;
	num = ft_strdup("./textures/door/Door1.xpm");
	while (i < 7)
	{
		increment_numbers(&num, i + 1);
		cub->door[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->door[i].width, &cub->door[i].height);
		cub->door[i].addr = mlx_get_data_addr
			(cub->door[i].img, &cub->door[i].bits_per_pixel,
				&cub->door[i].line_length, &cub->door[i].endian);
		cub->door[i].tmp_delay = 0;
		cub->door[i].delay = 7;
		i++;
	}
	free(num);
}

void	init_crown(t_cube *cub)
{
	int		i;
	char	*num;

	cub->crown = (t_txt *)malloc(8 * sizeof(t_txt));
	i = 0;
	num = ft_strdup("./textures/crown/crown1.xpm");
	while (i < 8)
	{
		increment_numbers(&num, i + 1);
		cub->crown[i].img = mlx_xpm_file_to_image
			(cub->con, num, &cub->crown[i].width, &cub->crown[i].height);
		cub->crown[i].addr = mlx_get_data_addr
			(cub->crown[i].img, &cub->crown[i].bits_per_pixel,
				&cub->crown[i].line_length, &cub->crown[i].endian);
		cub->crown[i].tmp_delay = 0;
		cub->crown[i].delay = 18;
		i++;
	}
	cub->crown->current_frame = 0;
	cub->crown->frame_max = 7;
	free(num);
}

void	init_main_menu_a(t_cube *cub)
{
	cub->main_menu_assets = (t_txt *)malloc(1 * sizeof(t_txt));
	cub->main_menu_assets[0].type = NULL;
	cub->main_menu_assets[0].path = ft_strdup
		("./textures/main_menu/title_main_menu.xpm");
}

void	init_alphabet(t_cube *cub)
{
	int		i;
	int		x;
	int		y;
	char	*num;

	i = 0;
	cub->abc = (t_txt *)malloc(26 * sizeof(t_txt));
	num = ft_strdup("./textures/alphabet/A.xpm");
	while (i < 26)
	{
		cub->abc[i].img = mlx_xpm_file_to_image(cub->con, num, &x, &y);
		cub->abc[i].addr = mlx_get_data_addr
			(cub->abc[i].img, &cub->abc[i].bits_per_pixel,
				&cub->abc[i].line_length, &cub->abc[i].endian);
		cub->abc[i].width = 22;
		cub->abc[i].height = 34;
		i++;
		increment_alphabet(num, i);
	}
	free(num);
}
